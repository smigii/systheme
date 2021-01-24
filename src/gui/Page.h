//
// Created by smigii on 2021-01-24.
//

#ifndef SYSTHEME_PAGE_H
#define SYSTHEME_PAGE_H

#include <string>

class Page {
private:
	// title

	// vector of
		// Input
		// Menu
		// TBlock (Text Blocks)

public:
	Page(std::string _title);

	// add_input()
	// add_menu()
	// add_tblock()

	// get_input(int i)
	// get_menu(int i)
	// get_tblock(int i)

	// activate()					// Draws all the ncurses shit to the screen.
	// deactivate()					// Deallocates all memory for the ncurses shit.
};


#endif //SYSTHEME_PAGE_H
