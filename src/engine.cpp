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
[[nodiscard]] umapstr extract_symbols(const fs::path& theme_path);

// Parse a validated template file line-by-line and process each line.
void process_template(const fs::path& tplate_file, const umapstr& symbol_map);

fs::path process_path(std::ifstream& ifs);

// --------------------------------------------------------------
// --- FHANDLE --------------------------------------------------

void STengine::process_config_theme(const std::string& program, const std::string& theme)
{
	// Validate template.* file
	fs::path program_dir {User::get_data_path() + program};
	fs::path tplate_file {get_template_file(program_dir)};
	if(tplate_file.empty()){
		std::cout << "NO TEMPLATE FILE AT " + program_dir.string() << std::endl;
		return;
	}

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

void STengine::process_systheme(const std::string& theme)
{

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
	return fs::path {""};
}

umapstr extract_symbols(const fs::path& theme_path)
{
	json js;
	umapstr table;
	std::ifstream ifs(theme_path);
	std::string delim {DELIM};

	ifs >> js;

	for(const auto& kvp : js["symbols"].items()){
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
	while(std::getline(ifs, raw_line)){
		std::string out {parser.process(raw_line)};
		ofs << out << std::endl;
		std::cout << out << std::endl;
	}

	std::cout << output.string() << std::endl;
//	if(!dst.empty())
//		fs::rename(output, dst);
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