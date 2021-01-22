//
// Created by smigii on 2021-01-12.
//

#include "WindowPane.h"

#include <iostream>

WindowPane::WindowPane(int sty, int stx, int siy, int six, int ny, int nx)
	: start_y{sty}, start_x{stx}, size_y{siy}, size_x{six}, num_y{ny}, num_x{nx} {
	vec_text = std::vector<std::string>();
	for(int i = 0; i < ny; i++){
		for(int j = 0; j < nx; j++){
			vec_text.push_back("test");
		}
	}
	build();
}
WindowPane::WindowPane(int sty, int stx, int siy, int six, int ny, int nx, std::vector<std::string> text)
: start_y{sty}, start_x{stx}, size_y{siy}, size_x{six}, num_y{ny}, num_x{nx}, vec_text{text} {
	build();
}

WindowPane::WindowPane(const WindowPane &wp) {
	start_y = wp.start_y;
	start_x = wp.start_x;
	size_y = wp.size_y;
	size_x = wp.size_x;
	num_y = wp.num_y;
	num_x = wp.num_y;

	vec_text = wp.vec_text;
	vec_win_obj = wp.vec_win_obj;

	build();

	std::cout << "copy const" << std::endl;
}
//WindowPane::WindowPane(WindowPane &&wp) {
//	start_y = wp.start_y;
//	start_x = wp.start_x;
//	size_y = wp.size_y;
//	size_x = wp.size_x;
//	num_y = wp.num_y;
//	num_x = wp.num_y;
//
//	vec_text = wp.vec_text;
//	vec_win_obj = wp.vec_win_obj;
//}
//WindowPane& WindowPane::operator=(WindowPane &&wp){
//	start_y = wp.start_y;
//	start_x = wp.start_x;
//	size_y = wp.size_y;
//	size_x = wp.size_x;
//	num_y = wp.num_y;
//	num_x = wp.num_y;
//
//	vec_text = wp.vec_text;
//	vec_win_obj = wp.vec_win_obj;
//
//	return *this;
//}

void WindowPane::build() {
//	if(vec_text.size() != num_y * num_x)
//		return;

	std::vector<int> y_vals;
	std::vector<int> x_vals;

//	win_matrix matrix;
	vec_win_obj.clear();

	int cell_yheight = size_y / num_y;
	int cell_xheight = size_x / num_x;

	for(int y = 0; y < num_y; y++){
		y_vals.push_back(start_y + y*(cell_yheight));
	}
	for(int x = 0; x < num_x; x++){
		x_vals.push_back(start_x + x*(cell_xheight));
	}

	for(int y = 0; y < y_vals.size(); y++){
		vec_win_obj.push_back(std::vector<WindowObj>());
		for(int x = 0; x < x_vals.size(); x++){
			WINDOW* temp_win = newwin(cell_yheight, cell_xheight, y_vals.at(y), x_vals.at(x));
			std::string temp_text = vec_text.at(y*num_x + x);
			vec_win_obj.at(y).push_back(WindowObj(temp_text, temp_win));
		}
	}

	test2 = true;

	refresh();
}

void WindowPane::draw() {
//	erase();
	for(int y = 0; y < vec_win_obj.size(); y++){
		for(int x = 0; x < vec_win_obj.at(0).size(); x++){
			vec_win_obj.at(y).at(x).enbox();
			wrefresh(vec_win_obj.at(y).at(x).get_win());
			vec_win_obj.at(y).at(x).print_title();
			wrefresh(vec_win_obj.at(y).at(x).get_win());
		}
	}
}

WindowObj* WindowPane::get_win(int y, int x) {
	return &vec_win_obj.at(y).at(x);
}

//void WindowPane::select_at(int y, int x) {
//	vec_win_obj.at(y).at(x).select();
//}
//void WindowPane::deselect_at(int y, int x) {
//	vec_win_obj.at(y).at(x).deselect();
//}

void WindowPane::set_titles(int h_align, std::vector<std::string> titles) {
	for(int y = 0; y < vec_win_obj.size(); y++){
		for(int x = 0; x < vec_win_obj.at(y).size(); x++){
			vec_win_obj.at(y).at(x).set_title(titles.at(y * num_x + x));
			vec_win_obj.at(y).at(x).set_h_align(h_align);
		}
	}
}

void WindowPane::test(){
	test2 = true;
}
