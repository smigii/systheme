//
// Created by smigii on 2021-01-12.
//

#include "WindowPane.h"

WindowPane::WindowPane(int sty, int stx, int siy, int six, int ny, int nx, std::vector<std::string> text)
: start_y{sty}, start_x{stx}, size_y{siy}, size_x{six}, num_y{ny}, num_x{nx}, vec_text{text} {

}

void WindowPane::build() {
//	if(vec_text.size() != num_y * num_x)
//		return;

	std::vector<int> y_vals;
	std::vector<int> x_vals;

//	win_matrix matrix;
	pane.clear();

	int cell_yheight = size_y / num_y;
	int cell_xheight = size_x / num_x;

	for(int y = 0; y < num_y; y++){
		y_vals.push_back(start_y + y*(cell_yheight));
	}
	for(int x = 0; x < num_x; x++){
		x_vals.push_back(start_x + x*(cell_xheight));
	}

	for(int y = 0; y < y_vals.size(); y++){
		pane.push_back(std::vector<WindowObj>());
		for(int x = 0; x < x_vals.size(); x++){
			WINDOW* temp_win = newwin(cell_yheight, cell_xheight, y_vals.at(y), x_vals.at(x));
			std::string temp_text = vec_text.at(y*num_x + x);
			pane.at(y).push_back(WindowObj(temp_text, temp_win));
		}
	}

	refresh();
}

void WindowPane::draw() {
//	erase();
	for(int y = 0; y < pane.size(); y++){
		for(int x = 0; x < pane.at(0).size(); x++){
			pane.at(y).at(x).enbox();
			wrefresh(pane.at(y).at(x).get_win());
			pane.at(y).at(x).print_text();
			wrefresh(pane.at(y).at(x).get_win());
		}
	}
}

void WindowPane::select_at(int y, int x) {
	pane.at(y).at(x).select();
}
void WindowPane::deselect_at(int y, int x) {
	pane.at(y).at(x).deselect();
}
