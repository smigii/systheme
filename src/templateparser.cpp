//
// Created by smigii on 2021-08-30.
//

#include "templateparser.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "utils/mrworldwide.h"
#include "utils/helpers.h"
#include "utils/exceptions.h"
#include "utils/opts.h"
#include "utils/user.h"
#include "utils/verbosityhandler.h"
#include "symbolmap.h"
#include "symbolnode.h"
#include "templateheader.h"

// --------------------------------------------------------------
// --- TLP Class ------------------------------------------------

class TemplateLineParser {

private:

	const t_symbolmap* symbol_map;
	const std::string open {OPEN};
	const std::string close {CLOSE};
	const size_t npos {std::string::npos};

	std::string current_line;
	std::ofstream& ofs;

	bool done {false};
	size_t prev_idx {0};
	size_t start_idx {0};
	size_t end_idx {0};
	size_t line_num {2}; // Since first line is DST and is not written

	[[nodiscard]] std::string strip_braces();
	[[nodiscard]] bool check_idxs() const;
	void process_next_symbol();
	void write_regular_segment();
	void next_symbol_idxs();
	void reset();

public:

	explicit TemplateLineParser(const t_symbolmap* symbol_map, std::ofstream& ofs);
	void process(std::string& line);

};


TemplateLineParser::TemplateLineParser(const t_symbolmap *symbol_map, std::ofstream& ofs)
: symbol_map{symbol_map}, ofs{ofs} {}


void TemplateLineParser::process(std::string& line)
{
	reset();
	current_line = line;
	next_symbol_idxs();
	prev_idx = 0; // otherwise would start at 0+1

	while(!done){
		done = check_idxs();
		write_regular_segment();
		process_next_symbol();
		next_symbol_idxs();
	}

	ofs << std::endl;
	line_num++;
}


void TemplateLineParser::process_next_symbol()
{
	if(done) return;
	std::string key {strip_braces()};
	systheme::utils::trim(key);

	const auto iter {symbol_map->find(key)};

	if(iter == symbol_map->end()){
		throw SysthemeException(
			"Error on line [" + std::to_string(line_num) + "], cannot find symbol: [" + key + "]"
		);
	}
	else
		iter->second->write_symbol(ofs);

}


std::string TemplateLineParser::strip_braces()
{
	size_t size { (end_idx - close.length()) - (start_idx + open.length()) + 1 };
	return current_line.substr(start_idx + open.length(), size);
}


bool TemplateLineParser::check_idxs() const
{
	 return start_idx == npos || end_idx == npos;
}


void TemplateLineParser::next_symbol_idxs()
{
	/*
	 * ABCD[%xxx%]EFGH[%yyy%]IJKL
	 * 	FIRST CALL:
	 * 		start_idx = 4
	 * 		end_idx = 10S
     *	SECOND CALL:
	 * 		start_idx = 15
	 * 		end_idx = 21
	 */
	if(done) return;
	prev_idx = end_idx + 1;
	start_idx = current_line.find(open, end_idx);
	if(start_idx == npos)
		end_idx = npos;
	else
		end_idx = current_line.find(close, start_idx + open.length() - 1) + (close.length() - 1);
}


void TemplateLineParser::reset()
{
	done = false;
	start_idx = end_idx = prev_idx = 0;
}


void TemplateLineParser::write_regular_segment()
{
	size_t end = std::min(current_line.length(), start_idx);
	size_t size = end - prev_idx;
	ofs << current_line.substr(prev_idx, size);
}

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

fs::path get_template_path(const std::string& program);

fs::path get_theme_path(const std::string& program, const std::string& theme);

bool prompt_confirm(const fs::path& tplate_path, const fs::path& output_file);

void backup(const fs::path& file_path);

// --------------------------------------------------------------
// --- HEADER IMPL ----------------------------------------------

void systheme::templates::process_template(const std::string &program, const std::string &theme)
{
	opts::VerbosityHandler vh;

	vh.out_2("finding [" + program + "] template");
	fs::path template_path {get_template_path(program)};
	fs::path theme_path {get_theme_path(program, theme)};
	t_symbolmap symbol_map {systheme::symbol::make_symbol_map(theme_path)};

	vh.out_2("processing template header...");
	systheme::templates::TemplateHeader header(template_path);

	std::ifstream ifs(template_path);
	fs::path output_path {header.get_dst()};
	std::string raw_line;
	// Move ifs to first line after header
	// -1 for off-by-one, -1 to move it back one for while loop below
	for (int i = 0; getline(ifs, raw_line) && i < header.get_first_line_num()-2; i++) {}

	// If simulation mode
	Opts* opts {Opts::instance()};
	if(opts->fl_s()){
		vh.out_1("SIMULATION MODE -- No changes written, no scripts run");
		return;
	}

	if(opts->fl_c() && !prompt_confirm(template_path, output_path)) return;
	if(opts->fl_b()) backup(output_path);

	// TODO: EW EW EW EW EW
	if(!header.get_pre_path().empty()) {
		vh.out_1("running pre-script: [" + header.get_pre_path().string() + "]");
		system(header.get_pre_path().string().c_str());
	}

	vh.out_1("writing to: [" + output_path.string() + "]");

	std::ofstream ofs(output_path);
	TemplateLineParser parser(&symbol_map, ofs);
	while(std::getline(ifs, raw_line)){
		parser.process(raw_line);
	}

	// TODO: EW EW EW EW EW
	if(!header.get_post_path().empty()) {
		vh.out_1("running post-script: [" + header.get_post_path().string() + "]");
		system(header.get_post_path().string().c_str());
	}
}

// --------------------------------------------------------------
// --- IMPLEMENTATION -------------------------------------------

fs::path get_template_path(const std::string& program)
{
	fs::path directory {User::get_data_path() / program};
	fs::directory_iterator dir_iter { directory };
	for(const fs::directory_entry& i : dir_iter){
		if(i.is_regular_file()){
			if(i.path().filename().string().find("template") != std::string::npos)
				return i.path();
		}
	}
	throw SysthemeException("No template file in directory: [" + directory.string() + "]");
}


fs::path get_theme_path(const std::string &program, const std::string &theme) {
	fs::path theme_path {User::get_data_path() / program / "themes" / theme};
	if(!fs::exists(theme_path))
		throw SysthemeException("Invalid theme path: [" + theme_path.string() + "]");
	return theme_path;
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


void backup(const fs::path& file_path)
{
	if(!fs::exists(file_path))
		throw SysthemeException("Invalid backup file given: [" + file_path.string() + "]");

	opts::VerbosityHandler vh;
	fs::path output { User::get_home() / ".systheme-backups" / file_path.filename() };

	fs::create_directories(output);
	output /= systheme::utils::get_time_stamp();
	vh.out_1("backing up [" + file_path.string() + "] to [" + output.string() + "]");
	fs::copy_file(file_path, output, fs::copy_options::overwrite_existing);
}