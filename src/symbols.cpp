//
// Created by smigii on 2021-09-01.
//

#include "symbols.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utils/exceptions.h"
#include "user.h"
#include "opts.h"

using json = nlohmann::json;

typedef std::unordered_map<std::string, t_symbolmap> t_scope_map;

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

/* Seems move semantics / NRVO don't work here, address of returned
 * json object differs from address of json created on stack. Will
 * need to return a pointer. */
std::unique_ptr<json> load_json_theme(const fs::path& theme_path);

t_scope_map make_scope_map(std::unique_ptr<json>& json);

t_symbolmap make_local_symbol_map(std::unique_ptr<json>& json, const t_scope_map& scope_map);

// --------------------------------------------------------------
// --- HEADER IMPLEMENTATIONS -----------------------------------

t_symbolmap systheme::make_symbol_map(const fs::path& theme_path)
{
	OPTS_VBOSE_1("creating symbol map for: [" + theme_path.string() + "]")
	// Load in JSON
	OPTS_VBOSE_2("loading JSON theme: [" + theme_path.string() + "]")
	std::unique_ptr<json> derulo {load_json_theme(theme_path)};

	// Create a map for specified includes.
	// Maps an include (program theme) to a symbol map.
	OPTS_VBOSE_2("handling includes for: [" + theme_path.string() + "]")
	t_scope_map scope_map {make_scope_map(derulo)};

	OPTS_VBOSE_2("finishing symbol map for: [" + theme_path.string() + "]")
	return {make_local_symbol_map(derulo, scope_map)};
}


// --------------------------------------------------------------
// --- IMPLEMENTATIONS ------------------------------------------

std::unique_ptr<json> load_json_theme(const fs::path& theme_path)
{
	// TODO: Should add some exception handling
	std::unique_ptr<json> statham {std::make_unique<json>()};
	std::ifstream ifs(theme_path);
	ifs >> *statham;
	return std::move(statham);
}


t_scope_map make_scope_map(std::unique_ptr<json>& json)
{
	t_scope_map scope_map;
	for(const auto& include : (*json)["includes"].items()){
		std::string inc_config {include.key()};
		std::string inc_theme {include.value()};
		fs::path path {User::get_data_path() / inc_config / "themes" / inc_theme};
		scope_map.insert(std::make_pair(inc_config, systheme::make_symbol_map(path)));
	}

	// Return address same as local address, NVRO confirmed
	return scope_map;
}


t_symbolmap make_local_symbol_map(std::unique_ptr<json>& json, const t_scope_map& scope_map)
{
	t_symbolmap result;

	for(const auto& kvp : (*json)["symbols"].items()){
		std::string key {kvp.key()};
		std::string val;
		if(kvp.value().type() == json::value_t::string)
			val = kvp.value();
		else if(kvp.value().type() == json::value_t::object){
			std::string scope = kvp.value().items().begin().key();
			std::string key = kvp.value().items().begin().value();
			val = scope_map.find(scope)->second.find(key)->second;
		}

		result.insert(std::make_pair(key, val));
	}

	// Return address same as local address, NVRO confirmed
	return result;
}