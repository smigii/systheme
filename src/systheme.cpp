#include <iostream>

#include "user.h"
#include "opts.h"
#include "engine.h"

int main(int argc, char* argv[]) {

	User::init();
	Opts::init(argc, argv);
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
 *  THEME FILE MACROS - These macros are to be used in json theme files.
 *      [%!FILE: /path/to/file%] -> Will return the contents of a file when queried
 *      "prompt": "[%!FILE: extra/minimal%] would replace any [%prompt%] symbols with
 *      the contents of the file ~/.config/systheme/data/CURRENT_CONFIG/extra/minimal.
 *      Relative paths would be relative to ~/.config/systheme/data/CURRENT_CONFIG
 *
 *
 */