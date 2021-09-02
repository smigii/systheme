//
// Created by smigii on 2021-09-01.
//

#ifndef SYSTHEME_SYMBOLS_H
#define SYSTHEME_SYMBOLS_H

#include <string>
#include <unordered_map>
#include <filesystem>

typedef std::unordered_map<std::string, std::string> t_symbolmap;

namespace fs = std::filesystem;

namespace systheme {

	t_symbolmap make_symbol_map(const fs::path& theme_path);

}

#endif //SYSTHEME_SYMBOLS_H
