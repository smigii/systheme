//
// Created by smigii on 2021-08-30.
//

#include "lineparser.h"

#include "user.h"

#include "utils/helpers.h"

LineParser::LineParser(const umapstr *symbol_map)
: symbol_map{symbol_map} {}

std::string LineParser::process(std::string& line)
{
	done = false;
	operand = line;
	start_idx = operand.find(open);
	end_idx = operand.find(close, start_idx + open.length());
	if(start_idx == npos || end_idx == npos) done = true;

	while(!done){
		process_next_symbol();
	}

	return operand;
}

void LineParser::process_next_symbol()
{
	std::string key {strip_braces()};
	trim(key);
	std::string val {process_key(key)};

	if(!val.empty()){
		size_t size = end_idx + close.length() - start_idx;
		operand.replace(start_idx, size, val);
	}
	else {
		operand = "";
		done = true;
	}

	start_idx = operand.find(open, start_idx + val.length());
	end_idx = operand.find(close, start_idx + open.length());
	if(start_idx == npos || end_idx == npos) done = true;
}

std::string LineParser::strip_braces()
{
	return operand.substr(start_idx + open.length(), end_idx - start_idx - close.length());
}


std::string LineParser::process_key(const std::string& key)
{
	std::string result;
	const auto iter {symbol_map->find(key)};

	// TODO: Implement missing symbol handling
	// Behavior should be specified by user.
	if(iter == symbol_map->end())
		result = "";
	else
		result = iter->second;

	return result;
}
