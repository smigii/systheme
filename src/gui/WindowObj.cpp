//
// Created by smigii on 2021-01-12.
//

#include "WindowObj.h"

WindowObj::WindowObj(std::string _text)
: text{_text} {

}
WindowObj::WindowObj(std::string _text, WINDOW* &_win)
	: text{_text}, win{_win} {

}

WINDOW *WindowObj::get_win() {
	return win;
}

void WindowObj::enbox() {
	box(win, 0, 0);
	wrefresh(win);
}

void WindowObj::print_text() {
	print_text(text);
}

void WindowObj::print_text(std::string t) {
	int maxx, maxy, x, y;

	getmaxyx(win, maxy, maxx);

	int text_offset = t.size()/2;

	x = maxx/2 - text_offset;
	y = maxy/2;

	mvwprintw(win, y, x, t.c_str());
	wrefresh(win);
}

void WindowObj::select() {
	wattron(win, A_REVERSE);
	print_text("> " + text + " <");
}

void WindowObj::deselect() {
	std::string space = "";
	for(int i = 0; i < text.size()+4; i++)
		space += " ";

	print_text(space);
}

