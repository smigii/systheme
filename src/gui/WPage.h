//
// Created by smigii on 2021-01-12.
//

#ifndef SYSTHEME_WPAGE_H
#define SYSTHEME_WPAGE_H

#include <vector>
#include <ncurses.h>

#include "WPane.h"

class WPage {
private:
	WObj* active_win;
	std::vector<WPane*> vec_pane;

public:
	WPage();
	WPage(std::vector<WPane*> _vec_pane);

//	void set_active(int vec_win_obj, int y, int x);
//	void set_active(WObj* wo_ptr);

	void add_pane(WPane* wpn);

	void build_pane(int pane);
	void build_all();

	void draw_pane(int pane);
	void draw_all();

	WObj* seek(int start_x, int start_y, int inc_x, int inc_y);
	void mv_r();
	void mv_l();
	void mv_u();
	void mv_d();

};


#endif //SYSTHEME_WPAGE_H
