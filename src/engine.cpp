//
// Created by smigii on 2021-08-29.
//

#include "engine.h"

#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utils/helpers.h"
#include "utils/mrworldwide.h"
#include "utils/exceptions.h"
#include "user.h"
#include "opts.h"
#include "symbols.h"
#include "lineparser.h"

namespace fs = std::filesystem;

using json = nlohmann::json;

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

[[nodiscard]] fs::path get_template_file(const fs::path& directory);

void process_template(const fs::path& tplate_path, const t_symbolmap& symbol_map);

[[nodiscard]] fs::path process_first_line(std::ifstream& ifs);

bool prompt_confirm(const fs::path& tplate_path, const fs::path& output_file);

bool prompt_abort();

void backup(const fs::path& file_path);

// --------------------------------------------------------------
// --- FHANDLE --------------------------------------------------

void systheme::apply_program_theme(const std::string& program, const std::string& theme)
{
	// Validate template.* file
	fs::path program_dir {User::get_data_path() / program};
	fs::path tplate_file {get_template_file(program_dir)};
	fs::path theme_path {program_dir / "themes" / theme};

	// Get the symbol map
	t_symbolmap symbol_map {systheme::symbols::make_symbol_map(theme_path)};
	try{ process_template(tplate_file, symbol_map); }
	catch(const SysthemeException& e) {
		throw SysthemeException("Error processing template: [" + tplate_file.string() + "]\n" + e.msg());
	}
}


void systheme::apply_system_theme(const std::string& theme)
{
	json derulo;
	std::ifstream ifs(Opts::get_theme_path());
	std::vector<std::string> errors;
	ifs >> derulo;

	for(const auto& kvp : derulo.items()){
		const std::string& program {kvp.key()};
		const std::string& conf_theme {kvp.value()};
		OPTS_VBOSE_1("\nprocessing config [" + program + "], theme [" + conf_theme + "]")
		try{ apply_program_theme(program, conf_theme); }
		catch(const SysthemeException& e) {
			std::string id {"*ERROR: program [" + program + "], theme [" + conf_theme + "]\n"};
			OPTS_VBOSE_1("\n" + id + e.msg())
			errors.push_back(id);
			if (prompt_abort()) {exit(-1);}
		}
	}

	if(!errors.empty()){
		OPTS_VBOSE_1("\nERROR REPORT:")
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
	throw SysthemeException("No template file in directory " + directory.string());
}

void process_template(const fs::path& tplate_path, const t_symbolmap& symbol_map)
{
	OPTS_VBOSE_1("processing template: [" + tplate_path.string() + "]")

	std::ifstream ifs(tplate_path);
	fs::path output_path {process_first_line(ifs)};
	if(!fs::exists(output_path))
		throw SysthemeException("Invalid target path " + output_path.string());
	std::string raw_line;

	// If simulation mode
	if(Opts::fl_s()){
		std::cout << "SIMULATION MODE -- No changes written\n";
		return;
	}

	if(Opts::fl_c() && !prompt_confirm(tplate_path, output_path)) return;
	if(Opts::fl_b()) backup(output_path);

	OPTS_VBOSE_1("writing to: [" + output_path.string() + "]")

	std::ofstream ofs(output_path);
	systheme::LineParser parser(&symbol_map, ofs);
	while(std::getline(ifs, raw_line)){
		parser.process(raw_line);
	}
}


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


bool prompt_confirm(const fs::path& tplate_path, const fs::path& output_file)
{
	std::cout << "CONFIRM OVERWRITE:\n"
	<< "template file: [" << tplate_path.string() << "]\n"
	<< "destination:   [" << output_file.string() << "]\n";

	char c {0};

	while( c != 'y' && c != 'Y' && c != 'n' && c != 'N' ){
		std::cout << "[y/n]: ";
		std::cin >> c;
	}

	return (c == 'y' || c == 'Y');
}


bool prompt_abort()
{
	std::cout << "\nWould you like to abort, or proceed to next config?" << std::endl;

	char c {0};

	while( c != 'a' && c != 'A' && c != 'p' && c != 'P' ){
		std::cout << "[A/a]bort, [P/p]roceed: ";
		std::cin >> c;
	}

	return (c == 'a' || c == 'A');
}


void backup(const fs::path& file_path)
{
	if(!fs::exists(file_path))
		throw SysthemeException("Invalid backup file given: [" + file_path.string() + "]");

	fs::path output { User::get_home() / ".systheme-backups" / file_path.filename() };

	fs::create_directories(output);
	output /= systheme::utils::get_time_stamp();
	OPTS_VBOSE_1("backing up [" + file_path.string() + "] to [" + output.string() + "]")
	fs::copy_file(file_path, output, fs::copy_options::overwrite_existing);
}