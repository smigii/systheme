#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "gui/ui.h"
#include "driver/Driver.h"
#include "tpc/Theme.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

int main() {

	ui();

	std::cout << "hello" << std::endl;

// ---------------------------------------------------------

//	Driver d;
//	try {
//		d.init();
//	} catch (std::string &e) {
//		std::cout << e << std::endl;
//	}
//	d.apply();

// ---------------------------------------------------------

	Theme t("Theme 1");

	t.add_program("Bash");
	t.at_prog(0)->add_conf("Bashrc", "/home/smigii/.bashrc");
	t.at_prog(0)->at_conf(0)->add_comp("Base1");
	t.at_prog(0)->at_conf(0)->add_comp("prompt/Minimal");
	t.at_prog(0)->at_conf(0)->add_comp("theme/Gruvbox");

	t.at_prog(0)->add_conf("Test", "/home/smigii/.test");
	t.at_prog(0)->at_conf(1)->add_comp("Base1");
	t.at_prog(0)->at_conf(1)->add_comp("prompt/testt");
	t.at_prog(0)->at_conf(1)->add_comp("theme/tesssst");

	t.add_program("Vim");
	t.at_prog(1)->add_conf(".vimrc", "/home/smigii/.vimrc");
	t.at_prog(1)->at_conf(0)->add_comp("Base1");
	t.at_prog(1)->at_conf(0)->add_comp("colors/Gruvbox");

	std::cout << t << std::endl;

	return 0;

}