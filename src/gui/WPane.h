//
// Created by smigii on 2021-01-12.
//

#ifndef SYSTHEME_WPANE_H
#define SYSTHEME_WPANE_H

#include <vector>
#include <ncurses.h>

#include "WObj.h"

class WPane {
private:
	int start_y, start_x, size_y, size_x, num_y, num_x;
	std::vector<std::string> vec_text;
	std::vector<std::vector<WObj>> vec_win_obj;

	bool test2;

public:
	WPane(int sty, int stx, int siy, int six, int ny, int nx);
	WPane(int sty, int stx, int siy, int six, int ny, int nx, std::vector<std::string> texts);
	WPane(const WPane &wp);
//	WPane(WPane &&wp);
//	WPane& operator=(WPane&& wp);

	void build();
	void draw();

	WObj* get_win(int y, int x);

	void set_titles(int h_align, std::vector<std::string> vec_titles);

	void test();
};


#endif //SYSTHEME_WPANE_H
