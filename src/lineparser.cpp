//
// Created by smigii on 2021-08-30.
//

#include "lineparser.h"

#include "utils/helpers.h"
#include "utils/exceptions.h"

systheme::LineParser::LineParser(const t_symbolmap *symbol_map, std::ofstream& ofs)
: symbol_map{symbol_map}, ofs{ofs} {}


void systheme::LineParser::process(std::string& line)
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


void systheme::LineParser::process_next_symbol()
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


std::string systheme::LineParser::strip_braces()
{
	size_t size { (end_idx - close.length()) - (start_idx + open.length()) + 1 };
	return current_line.substr(start_idx + open.length(), size);
}


bool systheme::LineParser::check_idxs() const
{
	 return start_idx == npos || end_idx == npos;
}


void systheme::LineParser::next_symbol_idxs()
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


void systheme::LineParser::reset()
{
	done = false;
	start_idx = end_idx = prev_idx = 0;
}


void systheme::LineParser::write_regular_segment()
{
	size_t end = std::min(current_line.length(), start_idx);
	size_t size = end - prev_idx;
	ofs << current_line.substr(prev_idx, size);
}
