//
// Created by smigii on 2021-09-02.
//

#include "symbolnode.h"

// --------------------------------------------------------------
// --- SymbolStringNode -----------------------------------------

systheme::SymbolStringNode::SymbolStringNode() = default;


systheme::SymbolStringNode::SymbolStringNode(std::string data)
: data{std::move(data)} {}


systheme::SymbolStringNode::SymbolStringNode(const systheme::SymbolStringNode &other)
: data{other.data} {}


systheme::SymbolStringNode::SymbolStringNode(systheme::SymbolStringNode &&other) noexcept
: data{other.data} {}


void systheme::SymbolStringNode::write_symbol(std::ofstream& ofs) const
{
	ofs << data;
}


std::string systheme::SymbolStringNode::get_data() const
{
	return data;
}

// --------------------------------------------------------------
// --- SymbolFileNode -------------------------------------------

systheme::SymbolFileNode::SymbolFileNode() = default;


systheme::SymbolFileNode::SymbolFileNode(fs::path path)
: path{std::move(path)} {}


systheme::SymbolFileNode::SymbolFileNode(const systheme::SymbolFileNode &other)
: path{other.path} {}


systheme::SymbolFileNode::SymbolFileNode(systheme::SymbolFileNode &&other) noexcept
: path{other.path} {}


void systheme::SymbolFileNode::write_symbol(std::ofstream& ofs) const
{
	std::ifstream ifs {path};
	std::string line;

	getline(ifs, line);
	ofs << line;

	while(getline(ifs, line)){
		ofs << std::endl << line;
	}
}


std::string systheme::SymbolFileNode::get_data() const
{
	return path.string();
}
