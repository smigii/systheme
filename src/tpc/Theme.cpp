//
// Created by smigii on 2021-01-21.
//

#include "Theme.h"

Theme::Theme(std::string _name)
: name{_name}{

}

std::ostream &operator<<(std::ostream &os, const Theme &theme) {
	os << "Theme [" << theme.name << "]\n";
	for(const std::unique_ptr<Program> &prog : theme.v_progs)
		os << *prog;

	return os;
}

std::string Theme::get_name() const {
	return name;
}

std::unique_ptr<Program> &Theme::at_prog(int i) const {
	return (std::unique_ptr<Program> &) v_progs.at(i);
}

void Theme::add_prog(std::string _name) {
	v_progs.push_back(std::make_unique<Program>(_name));
}
