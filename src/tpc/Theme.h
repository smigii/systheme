//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_THEME_H
#define SYSTHEME_THEME_H

#include <string>
#include <vector>
#include <memory>

#include "Program.h"

class Theme {
private:
	std::string name;
	std::vector<std::unique_ptr<Program>> v_progs;

public:
	Theme(std::string _name);

	friend std::ostream& operator<<(std::ostream& os, const Theme &theme);

	std::string get_name() const;

	std::unique_ptr<Program>& at_prog(int i) const;
	void add_program(std::string _name);
};


#endif //SYSTHEME_THEME_H
