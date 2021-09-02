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

/*
 * TODO:
 *
 *	CACHE RESULTS OF SYMBOL TABLES???
 *		It is possible the same symbol table will be included in multiple program
 *		themes (including alacritty in multiple themes to get 16 colors). Should
 *		have some kind of global cache that keeps track of what has been processed.
 *
 *
 *
 */