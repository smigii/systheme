//
// Created by smigii on 2021-08-30.
//

#ifndef SYSTHEME_LINEPARSER_H
#define SYSTHEME_LINEPARSER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "utils/mrworldwide.h"
#include "symbolnode.h"

typedef std::unordered_map<std::string, std::unique_ptr<systheme::SymbolNode>> t_symbolmap;

namespace systheme{

	// TODO: This whole class just feels kinda gross???
	class LineParser {

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

		explicit LineParser(const t_symbolmap* symbol_map, std::ofstream& ofs);

		void process(std::string& line);

	};

}


#endif //SYSTHEME_LINEPARSER_H
