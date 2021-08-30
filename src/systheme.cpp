#include <iostream>

#include "utils/exceptions.h"
#include "user.h"
#include "opts.h"
#include "engine.h"

int main(int argc, char* argv[]) {

	// Initialize and validate the User and Opts objects...
	User::init();

	Opts::init(argc, argv);
//	catch(const InvalidThemeException& e) {std::cout << e.msg() << std::endl;}

//	STengine::process_config_theme("alacritty/", "test.json");
	STengine::process_systheme(Opts::get_theme());

	return 0;

}

/*
 * TODO:
 *
 * ADD INCLUDES FUNCTIONALITY TO JSON SYMBOL FILES
 *     Should be able to include local symbols of other files,
 *     that way you could for example import terminal colors
 *     for use in other programs.
 *
 *     {
 *         "includes": [
 *             {"alacritty", "alc"}
 *         ],
 *         "symbols": {
 *             "sym1": "red"
 *             "sym2": {"alc", "normal-red"}
 *         }
 *     }
 *
 *     This would include the LOCAL symbols from data/alacritty/template.*
 *     to be accessed by "alc".
 *     The "sym2" symbol is accessing alc::normal-red.
 *
 *
 */