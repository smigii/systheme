//
// Created by smigii on 2021-01-11.
//

#include "Driver.h"

#include <filesystem>
#include <iostream>
#include <vector>

Driver::Driver(std::string root)
: root{root}{

}


std::string Driver::choose_program() {
	int i = 0;
	std::vector<std::string> vec_progs;
	for(const auto &entry : std::filesystem::directory_iterator(root + "programs/")){
		std::string theme_i = entry.path().filename().string();
		std::cout << i << ". " << theme_i << std::endl;
		vec_progs.push_back(theme_i);
		i++;
	}

	std::cout << "Please choose a program (number): ";
	int choice;
	while(choice <= 0 || choice > vec_progs.size()){
		std::cin >> choice;
	}
	return vec_progs.at(choice);
}


void Driver::create_theme() {
	int choice;
	std::cout << "1. Add program\n2. Finish\nEnter choice: ";
	std::cin >> choice;
	switch(choice){
		case 1:
			choose_program();
			// choose_file();
	}

}

void Driver::create_program(std::string name) {
	// Create a new directory of name prog_name under programs/
	std::filesystem::create_directory(root + "programs/" + name);
}

void Driver::create_config(std::string prog, std::string name) {
	// Create a new config file directory named conf_name for program prog_name.
	std::filesystem::create_directory(root + "programs/" + prog + "/" + name);
}

void Driver::create_bcomp(std::string prog, std::string conf, std::string name) {
	// Create a new base component for specified program and config file.

}

void Driver::create_mcomp(std::string prog, std::string conf, std::string mcomp, std::string name) {
	// Create a new base component for specified program and config file.
}




