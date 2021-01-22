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
	std::string title;
	WINDOW* win;

	int h_align;	// -1 L ; 0 C ; 1 R //

public:
	explicit WindowObj(std::string text);
	WindowObj(std::string text, WINDOW* &win);
	WindowObj(std::string text, WINDOW* &win, int h_align);

	WINDOW* get_win();

	void enbox();

	void set_h_align(int h);

	void set_title(std::string);
	void print_title();

};


#endif //SYSTHEME_WINDOWOBJ_H
