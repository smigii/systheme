//
// Created by smigii on 2021-08-29.
//

#include "engine.h"

#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>

#include "utils/GLOBALS.h"
#include "utils/helpers.h"
#include "user.h"
#include "opts.h"
#include "lineparser.h"

namespace fs = std::filesystem;
typedef std::unordered_map<std::string, std::string> umapstr;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

// Retrieve template.* file from directory.
[[nodiscard]] fs::path get_template_file(const fs::path& directory);

// Read from a validated .syth file to get the symbols needed.
// for replacement.
[[nodiscard]] umapstr extract_symbols(const fs::path& theme_path, bool parse_includes=true);

// Parse a validated template file line-by-line and process each line.
void process_template(const fs::path& tplate_file, const umapstr& symbol_map);

fs::path process_path(std::ifstream& ifs);

// --------------------------------------------------------------
// --- EXCEPTIONS -----------------------------------------------

class EngineException : public std::exception {
private:
	std::string message;

public:
	explicit EngineException(std::string message)
	: message{std::move(message)} {}

	[[nodiscard]] std::string msg () const noexcept { return message; }
};

// --------------------------------------------------------------
// --- FHANDLE --------------------------------------------------

void STengine::process_config_theme(const std::string& config, const std::string& theme)
{
	// Validate template.* file
	fs::path program_dir {User::get_data_path() / config};
	fs::path tplate_file {get_template_file(program_dir)};

	// Validate theme.syth file
	fs::path theme_path {program_dir.string() + "themes/" + theme};
	if(!fs::exists(theme_path)){
		std::cout << "THEME DOES NOT EXIST: " + theme_path.string();
		return;
	}

	// Get the symbol map
	umapstr symbol_map = extract_symbols(theme_path);

	process_template(tplate_file, symbol_map);

}

void STengine::process_systheme(const std::string& systheme)
{
	json derulo;
	std::ifstream ifs(Opts::get_theme_path());

	ifs >> derulo;

	for(const auto& kvp : derulo.items()){
		const std::string& config {kvp.key()};
		const std::string& conf_theme {kvp.value()};
		process_config_theme(config, conf_theme);
	}
}


// --------------------------------------------------------------
// --- IMPLEMENTATIONS ------------------------------------------

/// Searches for and retrieves any file named template
/// in the given directory, regardless of extension.
/// \param directory path of directory to search
/// \return path of template.* file
/// \throws EngineException error if no template file found.
fs::path get_template_file(const fs::path& directory)
{
	fs::directory_iterator dir_iter {directory};

	for(const fs::directory_entry& i : dir_iter){
		if(i.is_regular_file()){
			if(i.path().filename().string().find("template") != std::string::npos)
				return i.path();
		}
	}

	throw EngineException("No template file in directory " + directory.string());
}

umapstr extract_symbols(const fs::path& theme_path, bool parse_includes)
{
	json derulo;
	umapstr table;
	std::ifstream ifs(theme_path);
	std::string delim {DELIM};

	ifs >> derulo;

	// Handle includes
	if(parse_includes){
		std::cout << "INCLUDES:[";
		for(const auto& include : derulo["includes"]){
			std::cout << "\t" << include << "\n";
		}
		std::cout << "]\n";
	}

	for(const auto& kvp : derulo["symbols"].items()){
		std::string key {kvp.key()};
		std::string val {kvp.value()};
		table.insert(std::make_pair(key, val));
	}

	return table;
}

void process_template(const fs::path& tplate_file, const umapstr& symbol_map)
{
	std::ifstream ifs(tplate_file);
	fs::path output {process_path(ifs)};
	std::ofstream ofs(output);
	LineParser parser(&symbol_map);
	std::string raw_line;

	// If simulation mode
	if(Opts::fl_s())
		return;

	while(std::getline(ifs, raw_line)){
		std::string out {parser.process(raw_line)};
		ofs << out << std::endl;
		std::cout << out << std::endl;
	}
}

// Retreieves first line in a template file, which is the destination path.
fs::path process_path(std::ifstream& ifs)
{
	std::string open {OPEN};
	std::string close {CLOSE};
	std::string first_line;
	std::getline(ifs, first_line);
	fs::path o {User::expand_tilde_path(first_line.substr(open.length(), first_line.length() - open.length() - close.length()))};
	return o;
}