//
// Created by smigii on 2021-09-01.
//

#include "symbols.h"

#include <iostream>
#include <memory>
#include <fstream>
#include <nlohmann/json.hpp>

#include "utils/exceptions.h"
#include "utils/mrworldwide.h"
#include "lineparser.h"
#include "user.h"
#include "opts.h"
#include "symbolnode.h"

using json = nlohmann::json;

// --------------------------------------------------------------
// --- HELPER STRUCTS -------------------------------------------

struct key_value_scope {
	const std::string key;
	const std::string val;
	const t_scope_map& scope_map;

	key_value_scope(std::string key, std::string  val, const t_scope_map& scope_map)
	: key{std::move(key)}, val{std::move(val)}, scope_map{scope_map} {}
};

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

/* Seems move semantics / NRVO don't work here, address of returned
 * json object differs from address of json created on stack. Will
 * need to return a pointer. */
std::unique_ptr<json> load_json_theme(const fs::path& theme_path);

t_scope_map make_scope_map(std::unique_ptr<json>& json);

t_symbolmap make_local_symbol_map(std::unique_ptr<json>& json, const t_scope_map& scope_map);

std::unique_ptr<systheme::SymbolNode> handle_json_object(const key_value_scope& kvs);

std::unique_ptr<systheme::SymbolNode> process_directive(const key_value_scope& kvs);

std::unique_ptr<systheme::SymbolNode> process_scope(const key_value_scope& kvs);

// --------------------------------------------------------------
// --- HEADER IMPLEMENTATIONS -----------------------------------

t_symbolmap systheme::symbols::make_symbol_map(const fs::path& theme_path)
{
	try {
		std::string theme_name {User::format_theme_path(theme_path)};
		OPTS_VBOSE_1("creating symbol map for: [" + theme_name + "]")
		systheme::opts::VerboseIndentScope vis;

		// Load in JSON
		OPTS_VBOSE_2("loading JSON file: [" + theme_path.string() + "]")
		std::unique_ptr<json> derulo {load_json_theme(theme_path)};

		// Create a map for specified includes.
		// Maps an include (program theme) to a symbol map.
		OPTS_VBOSE_2("handling includes for: [" + theme_name + "]")
		t_scope_map scope_map {make_scope_map(derulo)};

		OPTS_VBOSE_2("finishing symbol map for: [" + theme_name + "]")
		return {make_local_symbol_map(derulo, scope_map)};
	}
	catch(const SysthemeException& e) {
		throw SysthemeException("Error processing theme " + theme_path.string() + "\n" + e.msg());
	}
}

// --------------------------------------------------------------
// --- IMPLEMENTATIONS ------------------------------------------

std::unique_ptr<json> load_json_theme(const fs::path& theme_path)
{
	if(!fs::exists(theme_path))
		throw SysthemeException("Theme does not exist: [" + theme_path.string() + "]");
	std::ifstream ifs(theme_path);
	std::unique_ptr<json> statham {std::make_unique<json>()};
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
		scope_map.insert(std::make_pair(inc_config, systheme::symbols::make_symbol_map(path)));
	}

	// Return address same as local address, NVRO confirmed
	return scope_map;
}


t_symbolmap make_local_symbol_map(std::unique_ptr<json>& json, const t_scope_map& scope_map)
{
	t_symbolmap result;

	for(const auto& kvp : (*json)["symbols"].items()){
		std::string key {kvp.key()};
		std::unique_ptr<systheme::SymbolNode> val;
		if(kvp.value().type() == json::value_t::string){
			val = std::make_unique<systheme::SymbolStringNode>(kvp.value());
		}
		else if(kvp.value().type() == json::value_t::object){
			std::string obj_key {kvp.value().items().begin().key()};
			std::string obj_val {kvp.value().items().begin().value()};
			key_value_scope kvs {obj_key, obj_val, scope_map};
			val = handle_json_object(kvs);
		}

		result.insert(std::make_pair(key, std::move(val)));
	}

	// Return address same as local address, NVRO confirmed
	return result;
}


std::unique_ptr<systheme::SymbolNode> handle_json_object(const key_value_scope& kvs)
{
	if(kvs.key.at(0) == DIRECTIVE_SYMBOL)
		return process_directive(kvs);
	else
		return process_scope(kvs);
}


std::unique_ptr<systheme::SymbolNode> process_directive(const key_value_scope& kvs)
{
	if(kvs.key == DIRECTIVE_FILE){
		fs::path input {kvs.val};
		if(input.root_directory() != "/")
			input = User::get_data_path() / input;
		if(!fs::exists(input))
			throw SysthemeException("!FILE directive argument does not exist: [" + input.string() + "]");
		return std::move(std::make_unique<systheme::SymbolFileNode>(input));
	} else {
		throw SysthemeException("Unknown directive: [" + kvs.key + "]");
	}
}


std::unique_ptr<systheme::SymbolNode> process_scope(const key_value_scope& kvs)
{
	std::string scope {kvs.key};
	std::string scope_key {kvs.val};

	const auto symbol_map_iterator = kvs.scope_map.find(scope);

	if(symbol_map_iterator == kvs.scope_map.end())
		throw SysthemeException("No included scope: [" + scope + "]");

	const auto result_iterator = symbol_map_iterator->second.find(scope_key);

	if(result_iterator == symbol_map_iterator->second.end())
		throw SysthemeException("Undefined symbol [" + scope_key + "] in [" + scope + "] scope");

	std::string data = result_iterator->second->get_data();
	return std::move(std::make_unique<systheme::SymbolStringNode>(data));
}