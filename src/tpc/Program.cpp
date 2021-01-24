//
// Created by smigii on 2021-01-21.
//

#include "Program.h"

#include <utility>

Program::Program(std::string _name)
: name{std::move(_name)} {

}

std::ostream &operator<<(std::ostream &os, const Program &prog) {
	os << "\tProgram [" << prog.name << "]\n";
	for(const std::unique_ptr<Config> &conf : prog.v_confs)
		os << *conf;

	return os;
}

std::string Program::get_name() const {
	return name;
}

std::unique_ptr<Config>& Program::at_conf(int i) const {
	return (std::unique_ptr<Config> &) v_confs.at(i);
}

void Program::add_conf(std::string _name, std::string _dest) {
	v_confs.push_back(std::make_unique<Config>(_name, _dest));
}
