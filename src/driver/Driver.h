//
// Created by smigii on 2021-01-11.
//

#ifndef SYSTHEME_DRIVER_H
#define SYSTHEME_DRIVER_H

#include <string>

class Driver {

private:

	std::string root;

public:

	Driver(std::string root);

	std::string choose_program();

	void create_theme();

	void create_program(std::string name);
	void create_config(std::string prog, std::string name);
	void create_bcomp(std::string prog, std::string conf, std::string name);
	void create_mcomp(std::string prog, std::string conf, std::string mcomp, std::string name);

	void apply();

};


#endif //SYSTHEME_DRIVER_H
