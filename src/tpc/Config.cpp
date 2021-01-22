//
// Created by smigii on 2021-01-21.
//

#include "Config.h"

#include <utility>

Config::Config(std::string _name, std::string _dest)
: name{std::move(_name)}, dest{std::move(_dest)} {

}

std::ostream& operator<<(std::ostream& os, const Config& conf) {
	os << "\t\tConfig [" << conf.name << "]\n";
	for(const std::string &comp : conf.v_comps){
		os << "\t\t\t" << comp << "\n";
	}
	return os;
}

std::string Config::get_name() const {
	return name;
}

std::string Config::get_dest() const {
	return dest;
}

std::string Config::get_comp(int i) const {
	return v_comps.at(i);
}

void Config::add_comp(const std::string& comp) {
	v_comps.push_back(comp);
}
