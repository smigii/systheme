//
// Created by smigii on 2021-01-12.
//

#include "WObj.h"

#include <utility>

WObj::WObj(std::string _text)
: title{std::move(_text)}, win{nullptr}, h_align{0} {
}
WObj::WObj(std::string _text, WINDOW* &_win)
	: title{std::move(_text)}, win{_win}, h_align{0} {
}
WObj::WObj(std::string _text, WINDOW* &_win, int _h_align)
	: title{std::move(_text)}, win{_win}, h_align{_h_align} {
}

WINDOW *WObj::get_win() {
	return win;
}

void WObj::enbox() {
	box(win, 0, 0);
	wrefresh(win);
}

void WObj::set_h_align(int h) {
	h_align = h;
}

void WObj::set_title(std::string t) {
	title = t;
}

void WObj::print_title() {
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



