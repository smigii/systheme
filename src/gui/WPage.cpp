//
// Created by smigii on 2021-01-12.
//

#include "WPage.h"

WPage::WPage() {
	active_win = nullptr;
}
WPage::WPage(std::vector<WPane*> _vec_pane) {
	vec_pane = _vec_pane;

//	set_active(0, 0, 0);
}

//void WPage::set_active(int vec_win_obj, int y, int x) {
//	if(active_win)
//		active_win->deselect();
//
//	vec_pane.at(vec_win_obj)->select_at(y, x);
//}
//void WPage::set_active(WObj *wo_ptr) {
//	active_win = wo_ptr;
//}

void WPage::add_pane(WPane* wp) {
	vec_pane.push_back(wp);
	wp->build();

//	if(!active_win) {
//		set_active(wp->get_win(0, 0));
//	}
}

void WPage::draw_pane(int pane) {
	vec_pane.at(pane)->build();
	vec_pane.at(pane)->draw();
}
void WPage::draw_all() {
	for(WPane* wpn : vec_pane){
		wpn->build();
		wpn->draw();
	}
}

void WPage::build_pane(int pane) {
	vec_pane.at(pane)->build();
}
void WPage::build_all() {
	for(WPane* wpn : vec_pane){
		wpn->build();
		wpn->test();
	}
}

WObj* WPage::seek(int start_x, int start_y, int inc_x, int inc_y) {
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
void WPage::mv_r() {

}
void WPage::mv_l() {

}
void WPage::mv_u() {

}
void WPage::mv_d() {

}
