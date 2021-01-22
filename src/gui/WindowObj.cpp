//
// Created by smigii on 2021-01-12.
//

#include "WindowObj.h"

#include <utility>

WindowObj::WindowObj(std::string _text)
: title{std::move(_text)}, win{nullptr}, h_align{0} {
}
WindowObj::WindowObj(std::string _text, WINDOW* &_win)
	: title{std::move(_text)}, win{_win}, h_align{0} {
}
WindowObj::WindowObj(std::string _text, WINDOW* &_win, int _h_align)
	: title{std::move(_text)}, win{_win}, h_align{_h_align} {
}

WINDOW *WindowObj::get_win() {
	return win;
}

void WindowObj::enbox() {
	box(win, 0, 0);
	wrefresh(win);
}

void WindowObj::set_h_align(int h) {
	h_align = h;
}

void WindowObj::set_title(std::string t) {
	title = t;
}

void WindowObj::print_title() {
	int xmax = getmaxx(win);
	int x;
	switch(h_align){
		case -1:
			x = 1;
			break;
		case 0:
			x = xmax/2 - title.size()/2;
			break;
		case 1:
			x = xmax - 1 - title.size();
	}

	mvwprintw(win, 1, x, title.c_str());
	wrefresh(win);
	mvwhline(win, 2, 1, ACS_HLINE, xmax - 2);
	wrefresh(win);
}



