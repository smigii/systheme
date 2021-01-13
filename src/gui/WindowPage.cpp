//
// Created by smigii on 2021-01-12.
//

#include "WindowPage.h"

WindowPage::WindowPage() {
	active_win = nullptr;
}
WindowPage::WindowPage(std::vector<WindowPane*> _vec_pane) {
	vec_pane = _vec_pane;

	set_active(0, 0, 0);
}

void WindowPage::set_active(int pane, int y, int x) {
	if(active_win)
		active_win->deselect();

	vec_pane.at(pane)->select_at(y, x);
}
void WindowPage::set_active(WindowObj *wo_ptr) {
	active_win = wo_ptr;
}

void WindowPage::add_pane(WindowPane* wp) {
	vec_pane.push_back(wp);
	wp->build();

	if(!active_win) {
		set_active(wp->get_win(0, 0));
	}
}

void WindowPage::draw_pane(int pane) {
	vec_pane.at(pane)->draw();
}
void WindowPage::draw_all() {
	for(WindowPane* wpn : vec_pane){
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
