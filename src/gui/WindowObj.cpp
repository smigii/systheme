//
// Created by smigii on 2021-01-12.
//

#include "WindowObj.h"

#include <utility>

WindowObj::WindowObj(std::string _text)
: title{std::move(_text)}, win{nullptr} {

}
WindowObj::WindowObj(std::string _text, WINDOW* &_win)
	: title{std::move(_text)}, win{_win} {

}
//WindowObj::WindowObj(const WindowObj &wo) {
//	title = wo.title;
//	win = wo.win;
//}

WINDOW *WindowObj::get_win() {
	return win;
}

void WindowObj::enbox() {
	box(win, 0, 0);
	wrefresh(win);
}

void WindowObj::print_text() {
	print_text(title);
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
	print_text("> " + title + " <");
	wattroff(win, A_REVERSE);
}

void WindowObj::deselect() {
	std::string space = "";
	for(int i = 0; i < title.size() + 4; i++)
		space += " ";

	print_text(space);
}

void WindowObj::set_title(std::string t) {
	title = t;
}

void WindowObj::print_title() {
	int xmax = getmaxx(win);
	int x = xmax/2 - title.size()/2;
	mvwprintw(win, 1, x, title.c_str());
	mvwhline(win, 2, 1, ACS_HLINE, xmax - 2);
}



