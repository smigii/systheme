//
// Created by smigii on 2021-01-12.
//

#ifndef SYSTHEME_WOBJ_H
#define SYSTHEME_WOBJ_H

#include <vector>
#include <string>
#include <ncurses.h>

class WObj {
private:
	std::string title;
	WINDOW* win;

	int h_align;	// -1 L ; 0 C ; 1 R //

public:
	explicit WObj(std::string text);
	WObj(std::string text, WINDOW* &win);
	WObj(std::string text, WINDOW* &win, int h_align);

	WINDOW* get_win();

	void enbox();

	void set_h_align(int h);

	void set_title(std::string);
	void print_title();

};


#endif //SYSTHEME_WOBJ_H
