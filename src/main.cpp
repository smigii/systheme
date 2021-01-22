#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "driver/Driver.h"

#include "driver/Program.h"
#include "driver/Config.h"
#include "driver/Theme.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

int main() {

//	Driver d;
//	try {
//		d.init();
//	} catch (std::string &e) {
//		std::cout << e << std::endl;
//	}
//	d.apply();

// -------------

//	Config c("Config 1", "/home/upYourAss");
//	c.add_comp("c1");
//	c.add_comp("c2");
//	c.add_comp("c3");
//
//	Program p("Program 1");
//	p.add_conf(c);
//	p.add_conf(c);
//
//	std::cout << p << std::endl;

// ----------------

	Program p("Program 1");

	p.add_conf("Config 1", "/home/FuckYou");
	p.add_conf("Config 2", "/home/FuckYourFace");

	p.at_conf(0)->add_comp("C1");
	p.at_conf(0)->add_comp("C2");
	p.at_conf(0)->add_comp("C3");

	p.at_conf(1)->add_comp("C1");
	p.at_conf(1)->add_comp("C2");
	p.at_conf(1)->add_comp("C3");

	std::cout << p << std::endl;


	return 0;

}