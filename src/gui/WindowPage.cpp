//
// Created by smigii on 2021-01-12.
//

#include "WindowPage.h"

WindowPage::WindowPage() {
	active_win = nullptr;
}
WindowPage::WindowPage(std::vector<WindowPane*> _vec_pane) {
	vec_pane = _vec_pane;

//	set_active(0, 0, 0);
}

//void WindowPage::set_active(int vec_win_obj, int y, int x) {
//	if(active_win)
//		active_win->deselect();
//
//	vec_pane.at(vec_win_obj)->select_at(y, x);
//}
//void WindowPage::set_active(WindowObj *wo_ptr) {
//	active_win = wo_ptr;
//}

void WindowPage::add_pane(WindowPane* wp) {
	vec_pane.push_back(wp);
	wp->build();

//	if(!active_win) {
//		set_active(wp->get_win(0, 0));
//	}
}

void WindowPage::draw_pane(int pane) {
	vec_pane.at(pane)->build();
	vec_pane.at(pane)->draw();
}
void WindowPage::draw_all() {
	for(WindowPane* wpn : vec_pane){
		wpn->build();
		wpn->draw();
	}
}

void WindowPage::build_pane(int pane) {
	vec_pane.at(pane)->build();
}
void WindowPage::build_all() {
	for(WindowPane* wpn : vec_pane){
		wpn->build();
		wpn->test();
	}
}

WindowObj* WindowPage::seek(int start_x, int start_y, int inc_x, int inc_y) {
	int x {start_x};
	int y {start_y};

	int MAXX, MAXY;
	getmaxyx(stdscr, MAXY, MAXX);

	while(x > 0 && x < MAXX && y > 0 && y < MAXY){



		x += inc_x;
		y += inc_y;
	}

	return nullptr;
}
void WindowPage::mv_r() {

}
void WindowPage::mv_l() {

}
void WindowPage::mv_u() {

}
void WindowPage::mv_d() {

}
