#include <iostream>

#include "user.h"
#include "opts.h"
#include "engine.h"

int main(int argc, char* argv[]) {

	User::init();
	Opts::init(argc, argv);
	systheme::apply_system_theme(Opts::get_theme());
//	t_symbolmap t = systheme::make_symbol_map("/home/smigii/.config/systheme2/data/i3/themes/gruvbox.json");

	return 0;

}

/* ----------------------------------------------------------------------------
 *	TODO: TEMPLATE HEADER REWORK
 *
 *		Template headers should be checked more thouroughly.
 *		Syntax as following...
 *		[%
 *		DST /path/to/destination
 *		REFRESH /path/to/refresh/script
 *		--more to come--
 *		%]
 *		Should just tokenize and parse, ignoring whitespace.
 *
 *
 *
 *	TODO: REFRESH SCRIPTS
 *
 *		Implement (safely) refresh scripts.
 *		Scrip path should be in template header.
 *
 *
 *
 *	TODO: CONVERT LINE PARSER TO PARSER
 *
 *		No reason to have a LineParser, we are only ever processing a full
 *		file, not a just a few lines.
 *
 *
 *
 * 	TODO: LOCAL VARIABLES IN PROGRAM THEMES
 *
 * 		In addition to "includes" and "symbols", add a "locals" section which
 * 		defines local variables. Example
 *		"locals" : {
 *			"var1" : "#282828"
 *		},
 *		"symbols" {
 *			"some_color" : {"%LOCAL" : "var1"}
 *		}
 *
 *
 *
 *	TODO: CACHE RESULTS OF SYMBOL TABLES???
 *
 *		It is possible the same symbol table will be included in multiple
 *		program themes (including alacritty in multiple themes to get 16
 *		colors). Should have some kind of global cache that keeps track of
 *		what has been processed.
 *
 *
 *
 * ------------------------------------------------------------------------- */