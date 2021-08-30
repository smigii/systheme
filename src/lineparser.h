//
// Created by smigii on 2021-08-30.
//

#ifndef SYSTHEME_LINEPARSER_H
#define SYSTHEME_LINEPARSER_H

#include <string>
#include <unordered_map>
#include <filesystem>

#include "utils/GLOBALS.h"

namespace fs = std::filesystem;
typedef std::unordered_map<std::string, std::string> umapstr;

class LineParser {

private:
	fs::path dst;
	const umapstr* symbol_map;
	const std::string open {OPEN};
	const std::string close {CLOSE};
	std::string operand;
	bool done {false};

	size_t start_idx {0};
	size_t end_idx {0};
	size_t npos {std::string::npos};

	[[nodiscard]] std::string strip_braces();

	[[nodiscard]] std::string process_key(const std::string& key);

	// Finds the next symbol in the operand and replaces it with the
	// value from the symbol table.
	void process_next_symbol();

	void process_dst(const std::string& path);

public:

	explicit LineParser(const umapstr* symbol_map);

	std::string process(std::string& line);

	[[nodiscard]] fs::path get_dst() const;

};


#endif //SYSTHEME_LINEPARSER_H
