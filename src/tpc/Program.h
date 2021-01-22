//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_PROGRAM_H
#define SYSTHEME_PROGRAM_H

#include <string>
#include <vector>
#include <ostream>
#include <memory>

#include "Config.h"

class Program {
private:
	std::string name;
	std::vector<std::unique_ptr<Config>> v_confs;

public:
	Program(std::string _name);

	friend std::ostream& operator<<(std::ostream& os, const Program &prog);

	std::string get_name() const;

	std::unique_ptr<Config>& at_conf(int i) const;
	void add_conf(std::string _name, std::string _dest);
};


#endif //SYSTHEME_PROGRAM_H
