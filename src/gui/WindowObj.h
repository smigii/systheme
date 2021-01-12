//
// Created by smigii on 2021-01-12.
//

#ifndef SYSTHEME_WINDOWOBJ_H
#define SYSTHEME_WINDOWOBJ_H

#include <vector>
#include <string>
#include <ncurses.h>

class WindowObj {
private:
	std::string text;
	WINDOW* win;

public:
	WindowObj(std::string text);
	WindowObj(std::string text, WINDOW* &win);

	WINDOW* get_win();

	void enbox();

	void print_text();
	void print_text(std::string t);

	void select();
	void deselect();

};


#endif //SYSTHEME_WINDOWOBJ_H
