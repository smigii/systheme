//
// Created by smigii on 2021-01-12.
//

#ifndef SYSTHEME_WINDOWPANE_H
#define SYSTHEME_WINDOWPANE_H

#include <vector>
#include <ncurses.h>

#include "WindowObj.h"

class WindowPane {
private:
	int start_y, start_x, size_y, size_x, num_y, num_x;
	std::vector<std::string> vec_text;
	std::vector<std::vector<WindowObj>> vec_win_obj;

	bool test2;

public:
	WindowPane(int sty, int stx, int siy, int six, int ny, int nx);
	WindowPane(int sty, int stx, int siy, int six, int ny, int nx, std::vector<std::string> texts);
	WindowPane(const WindowPane &wp);
//	WindowPane(WindowPane &&wp);
//	WindowPane& operator=(WindowPane&& wp);

	void build();
	void draw();

	WindowObj* get_win(int y, int x);

	void set_titles(int h_align, std::vector<std::string> vec_titles);

	void test();
};


#endif //SYSTHEME_WINDOWPANE_H
