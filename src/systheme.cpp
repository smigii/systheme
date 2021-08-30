#include <iostream>

#include "utils/exceptions.h"
#include "user.h"
#include "opts.h"
#include "engine.h"

int main(int argc, char* argv[]) {

	// Initialize and validate the User and Opts objects...
	User::init();
//	try {const Opts opts = Opts(argc, argv);}
//	catch(const InvalidThemeException& e) {std::cout << e.msg() << std::endl;}

	STengine::process_config_theme("alacritty/", "test.syth");

	return 0;

}