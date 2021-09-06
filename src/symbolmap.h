//
// Created by smigii on 2021-09-01.
//

#ifndef SYSTHEME_SYMBOLMAP_H
#define SYSTHEME_SYMBOLMAP_H

#include <string>
#include <unordered_map>
#include <filesystem>
#include <memory>

namespace systheme {
	class SymbolNode;
}

typedef std::unordered_map<std::string, std::unique_ptr<systheme::SymbolNode>> t_symbolmap;
typedef std::unordered_map<std::string, t_symbolmap> t_scopemap;

namespace fs = std::filesystem;

namespace systheme::symbol {

	t_symbolmap make_symbol_map(const fs::path& theme_path);

}

#endif //SYSTHEME_SYMBOLMAP_H
