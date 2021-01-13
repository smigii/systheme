//
// Created by smigii on 2021-01-12.
//

#ifndef SYSTHEME_WINDOWPAGE_H
#define SYSTHEME_WINDOWPAGE_H

#include <vector>
#include <ncurses.h>

#include "WindowPane.h"

class WindowPage {
private:
	WindowObj* active_win;
	std::vector<WindowPane*> vec_pane;

public:
	WindowPage();
	WindowPage(std::vector<WindowPane*> _vec_pane);

	void set_active(int pane, int y, int x);
	void set_active(WindowObj* wo_ptr);

	void add_pane(WindowPane* wpn);

	void build_pane(int pane);
	void build_all();

	void draw_pane(int pane);
	void draw_all();


};


#endif //SYSTHEME_WINDOWPAGE_H