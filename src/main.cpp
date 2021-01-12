#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <curses.h>
#include <filesystem>

#include "driver/Driver.h"

#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

typedef std::vector<std::vector<WINDOW*>> win_matrix;

/*
 * So, let's start off by just hardcoding a bunch of shit.
 *
 * TODO:
 * 1. Write a c++ implementation of the bash scripts we are already using to change themes.
 * 		1a. Bash
 * 		1b. Vim
 * 		1c. Alacritty
 * 		1d. i3
 *
 */

win_matrix win_builder(int start_y, int start_x, int size_y, int size_x, int num_y, int num_x){
	std::vector<int> y_vals;
	std::vector<int> x_vals;

	win_matrix matrix;

	int cell_yheight = size_y / num_y;
	int cell_xheight = size_x / num_x;

	for(int y = 0; y < num_y; y++){
		y_vals.push_back(start_y + y*(cell_yheight));
	}
	for(int x = 0; x < num_y; x++){
		x_vals.push_back(start_x + x*(cell_xheight));
	}

	for(int y = 0; y < y_vals.size(); y++){
		matrix.push_back(std::vector<WINDOW*>());
		for(int x = 0; x < x_vals.size(); x++){
			matrix.at(y).push_back(newwin(cell_yheight, cell_xheight, y_vals.at(y), x_vals.at(x)));
		}
	}

	return matrix;
}

int main() {

	initscr();

	int XMAX, YMAX;
	getmaxyx(stdscr, YMAX, XMAX);

//	WINDOW* win_app = newwin(YMAX/2, XMAX/2, 0, 0);
//	WINDOW* win_cre = newwin(YMAX/2, XMAX/2, 0, XMAX/2 + (XMAX%2 != 0));
//	WINDOW* win_del = newwin(YMAX/2, XMAX/2, YMAX/2 + (YMAX%2 != 0), 0);
//	WINDOW* win_edi = newwin(YMAX/2, XMAX/2, YMAX/2 + (YMAX%2 != 0), XMAX/2 + (XMAX%2 != 0));

	win_matrix winv_home = win_builder(0, 0, YMAX, XMAX, 2, 2);

	refresh();

	box(winv_home.at(0).at(0), 0, 0);
	box(winv_home.at(0).at(1), 0, 0);
	box(winv_home.at(1).at(0), 0, 0);
	box(winv_home.at(1).at(1), 0, 0);

	wprintw(winv_home.at(0).at(0), "Apply Theme");
	wprintw(winv_home.at(0).at(1), "Create Theme");
	wprintw(winv_home.at(1).at(0), "Delete Theme");
	wprintw(winv_home.at(1).at(1), "Edit Theme");

	wrefresh(winv_home.at(0).at(0));
	wrefresh(winv_home.at(0).at(1));
	wrefresh(winv_home.at(1).at(0));
	wrefresh(winv_home.at(1).at(1));

//	mvaddstr(2, 2, "HELLO");

	getch();
	endwin();

//	using json = nlohmann::json;

	Driver d("/home/smigii/.config/systheme/");

	return 0;
}


void old(){
	std::string root = "/home/smigii/.config/systheme/";

	// BASH
	// Print out list of bash themes
	std::string path = root + "programs/bash/bashrc/mcomp-themes/";
	std::vector<std::string> vec_themes;

	int i = 1;
	std::cout << "Please enter a theme to use:" << std::endl;
	for(const auto &entry : fs::directory_iterator(path)){
		std::string theme_i = entry.path().filename().string();
		std::cout << i << ". " << theme_i << std::endl;
		vec_themes.push_back(theme_i);
		i++;
	}
	// Get user to select one
	std::cout << "Enter a choice between 1 and " << vec_themes.size() << ": ";
	int choice;
	while(choice <= 0 || choice > vec_themes.size()){
		std::cin >> choice;
	}

	std::cout << "[" << vec_themes.at(choice - 1) << "]" << " selected." << std::endl;

	// Overwrite .bashrc
	// Create bashrc_temp file.
	// For this example, follow BASE1 -> THEME -> PROMPT
	std::fstream file;
	std::ofstream ofile(root + "programs/bash/bashrc/out", std::ios::out | std::ios::app);

	std::ifstream ifile(root + "programs/bash/bashrc/bcomp-base1");
	ofile << ifile.rdbuf();

	std::string test = "\n\ntest.\n";
	ofile << "\n\nHELLO";

	std::ofstream("../test2.png", std::ios::binary) << std::ifstream("../test.png", std::ios::binary).rdbuf();
}