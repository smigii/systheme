//
// Created by smigii on 2021-08-29.
//

#include "engine.h"

#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utils/GLOBALS.h"
#include "user.h"
#include "opts.h"
#include "symbols.h"
#include "lineparser.h"

namespace fs = std::filesystem;

using json = nlohmann::json;

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

/// Searches for and retrieves any file named template
/// in the given directory, regardless of extension.
/// \param directory path of directory to search
/// \return path of template.* file
/// \throws EngineException error if no template file found.
[[nodiscard]] fs::path get_template_file(const fs::path& directory);

// Parse a validated template file line-by-line and process each line.
void process_template(const fs::path& tplate_file, const t_symbolmap& symbol_map);

fs::path process_first_line(std::ifstream& ifs);

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

void systheme::apply_program_theme(const std::string& program, const std::string& theme)
{
	// Validate template.* file
	fs::path program_dir {User::get_data_path() / program};
	fs::path tplate_file {get_template_file(program_dir)};

	// Validate theme.json file
	fs::path theme_path {program_dir.string() + "themes/" + theme};
	if(!fs::exists(theme_path)){
		throw EngineException("Theme [" + theme + "] does not exist at [" + theme_path.string() + "]");
	}

	// Get the symbol map
	t_symbolmap symbol_map {systheme::make_symbol_map(theme_path)};

	process_template(tplate_file, symbol_map);
}

void systheme::apply_system_theme(const std::string& theme)
{
	json derulo;
	std::ifstream ifs(Opts::get_theme_path());
	std::vector<std::string> errors;
	ifs >> derulo;

	for(const auto& kvp : derulo.items()){
		const std::string& config {kvp.key()};
		const std::string& conf_theme {kvp.value()};
		IF_VERBOSE("\nprocessing config [" + config + "], theme [" + conf_theme + "]\n")
		try{ apply_program_theme(config, conf_theme); }
		catch(const EngineException& e) {
			IF_VERBOSE("ERROR: " + e.msg())
			std::string id {"*ERROR: config [" + config + "], theme [" + conf_theme + "]\n"};
			errors.push_back(id + e.msg());
		}
	}

	if(!errors.empty()){
		IF_VERBOSE_ENDL("\nERROR REPORT:")
		for(const std::string& err : errors)
			std::cout << err << "\n\n";
	}
}


// --------------------------------------------------------------
// --- IMPLEMENTATIONS ------------------------------------------


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

// This is fucking disgusting and needs to be optimized
// return a unique pointer
umapstr extract_symbols(const fs::path& theme_path)
{
	json derulo;
	std::ifstream ifs(theme_path);
	std::string delim {DELIM};
	umapstr result;

	ifs >> derulo;

	// Handle includes
	std::unordered_map<std::string, umapstr> scopes;
	for(const auto& include : derulo["includes"].items()){
		std::string inc_config {include.key()};
		std::string inc_theme {include.value()};
		fs::path path {User::get_data_path() / inc_config / "themes" / inc_theme};
		scopes.insert(std::make_pair(inc_config, extract_symbols(path)));
	}

	for(const auto& kvp : derulo["symbols"].items()){
		std::string key {kvp.key()};
		std::string val;
		if(kvp.value().type() == json::value_t::string)
			val = kvp.value();
		else if(kvp.value().type() == json::value_t::object){
			std::string scope = kvp.value().items().begin().key();
			std::string key = kvp.value().items().begin().value();
			val = scopes.find(scope)->second.find(key)->second;
		}
		result.insert(std::make_pair(key, val));
	}

	return result;
}

void process_template(const fs::path& tplate_file, const t_symbolmap& symbol_map)
{
	IF_VERBOSE_ENDL("processing template: [" + tplate_file.string() + "]")

	std::ifstream ifs(tplate_file);
	fs::path output {process_first_line(ifs)};
	if(!fs::exists(output))
		throw EngineException("Invalid target path " + output.string());
	std::ofstream ofs(output);
	LineParser parser(&symbol_map);
	std::string raw_line;

	// If simulation mode
	if(Opts::fl_s())
		return;

	IF_VERBOSE_ENDL("writing to: [" + output.string() + "]")

	while(std::getline(ifs, raw_line)){
		std::string out {parser.process(raw_line)};
		ofs << out << std::endl;
	}
}

// Retreieves first line in a template file, which is the destination path.
fs::path process_first_line(std::ifstream& ifs)
{
	std::string open {OPEN};
	std::string close {CLOSE};
	std::string first_line;
	std::getline(ifs, first_line);
	// [%~/path/to/dst%] -> /home/user/path/to/dst
	fs::path o {User::expand_tilde_path(first_line.substr(open.length(), first_line.length() - open.length() - close.length()))};
	return o;
}