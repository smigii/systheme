#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <curses.h>
#include <filesystem>

#include "driver/Driver.h"

#include "gui/WindowPage.h"
#include "gui/WindowPane.h"
#include "gui/WindowObj.h"

#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

int main() {

	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_RED);

	int XMAX, YMAX;
	getmaxyx(stdscr, YMAX, XMAX);
//	XMAX = YMAX = 50;

	std::vector<std::string> titles{"Apply Theme", "Create Theme", "Edit Theme", "Delete Theme"};
	std::vector<std::string> test{"TEST1", "TEST2"};

	WindowPane wpn_home = WindowPane(YMAX / 4, XMAX / 5, YMAX / 2, 3 * XMAX / 5, 2, 2, titles);
	WindowPane wpn_test = WindowPane(0, 0, YMAX, XMAX/2, 1, 2, test);

	WindowPage wpg_main = WindowPage();
	WindowPage wpg_test = WindowPage();

	wpg_main.add_pane(&wpn_home);
	wpg_test.add_pane(&wpn_test);

	wpg_main.draw_all();
	getch();

	wpg_test.build_all();
	wpg_test.draw_all();
	getch();

//	char choice = getch();
//	while(choice != 'q'){
//		switch(choice){
//			case 'h':
//				wpn_home.select_at(0, 0);
//				break;
//			case 'j':
//				wpn_home.select_at(0, 1);
//				break;
//			case 'k':
//				wpn_home.select_at(1, 0);
//				break;
//			case 'l':
//				wpn_home.select_at(1, 1);
//				break;
//		}
//		choice = getch();
//	}


	getch();
	endwin();

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