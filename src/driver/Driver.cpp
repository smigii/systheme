//
// Created by smigii on 2021-01-21.
//

/* ================================================================================================
 * TODO:
 * 		getlogin() will not work on daemonized processes. Will need handle for that.
 * ================================================================================================ */

#include "Driver.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>		// getlogin_r()

#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace fs = std::filesystem;

Driver::Driver()
: user{""}, root{""}{

}

void Driver::init(){
	// Get the user
	char* c_user = getlogin();
	if(c_user){
		user = c_user;
	} else {
		std::string msg = "\tFailed to get user login name using getlogin_r(char* name, size_t bufsize).";
		throw std::runtime_error(msg);
	}

	// Check that there is a /home/USER directory
	if(!fs::is_directory("/home/" + user)){
		std::string msg = "\tDirectory does not exist : [/home/" + user + "/]";
		throw std::runtime_error(msg);
	}

	// Check that there is a /home/USER/.Config/systheme directory
	// If there isn't, prompt user to create one. Creation should be handled by a setup script
	// Set the "root" attr to "/home/USER/.Config/systheme"
	if(!fs::is_directory("/home/" + user + "/.Config/systheme/") && !init_config_dir_prompt()){
		std::string msg {
			"\tDirectory does not exist : /home/" + user + "/.Config/systheme/\n" +
			"\tPlease create this directory before continuing."
		};
		throw std::runtime_error(msg);
	} else {
		root = "/home/" + user + "/.Config/systheme/";
	}
}

// Prompts user to create the ~/.Config/systheme directory.
// Returns true if created, false if denied.
bool Driver::init_config_dir_prompt() {
	std::cout << "Directory not found : [~/.Config/systheme/]\n\tWould you like to create it now?\n";
	char c {'0'};
	do{
		std::cout << "\t[y/n] : ";
		std::cin >> c;
	} while(c != 'y' && c != 'n');

	if(c == 'y') {
		if(!fs::is_directory("/home/" + user + "/.Config")){
			fs::create_directory("/home/" + user + "/.Config/");
		}
		fs::create_directory("/home/" + user + "/.Config/systheme/");
		return true;
	} else {
		return false;
	}
}

// ========================================================================================== //
// ===== APPLY ============================================================================== //
// ========================================================================================== //

void Driver::apply() {
	std::string choice = apply_io();		// Show all Theme options and get json file (Theme) to use.
	json jtheme = apply_init_json(choice);	// Initialize the json object.
	apply_execute(jtheme);				// Write the files.
}

// Displays all possible themes for the user,
// then prompts user to select one.
std::string Driver::apply_io() {
	std::vector<std::string> vec_themes;

	// ----- Display Themes ----- //
	int i = 1;
	std::cout << "Themes for user [" << user << "]" << std::endl;
	for(const fs::directory_entry &entry : fs::directory_iterator(root + "themes/")){
		std::string theme_i = entry.path().filename().string();
		std::cout << "\t" << i << ". " << theme_i << std::endl;
		vec_themes.push_back(theme_i);
		i++;
	}

	// ----- User Input ----- //
	int num_opts = vec_themes.size();
	int choice {-1};
	while(choice < 1 || choice >= vec_themes.size()){
		std::cout << "Enter a choice between [1, " << num_opts << "]: ";
		std::cin >> choice;
		choice--;
	}
	std::cout << "[" << vec_themes.at(choice) << "]" << " selected." << std::endl;

	return vec_themes.at(choice);
}

// Initializes the JSON object.
json Driver::apply_init_json(const std::string& theme) {
	std::ifstream ifs(root + "themes/" + theme);
	json jtheme;
	ifs >> jtheme;

	return jtheme;
}

bool Driver::apply_execute(json &jtheme) {
	// Now we build
	std::cout << "\n========== SYSTHEME 0.0.1 ==========\n";
	// Loop through the Program layer...
	for(const auto &prog : jtheme){
		std::cout << "Building Program [" << std::string(prog["name"]) << "]" << std::endl;
		for(const auto &conf : prog["configs"]){
			// Loop through the Config file layer...
			std::cout << "\tBuilding Config [" << std::string(conf["name"]) << "]" << std::endl;

			std::string o_path {conf["dest"]};

			std::ofstream trunc(o_path, std::ios::out | std::ios::trunc);
			trunc.close();

			std::ofstream ofile(o_path, std::ios::out | std::ios::app);
			std::string i_path {root + "data/" + std::string(prog["name"]) + "/" + std::string(conf["name"]) + "/" };

			std::cout << "\t\tConfig location: " + o_path << std::endl;

			for(const auto &comp : conf["components"]){
				std::cout << "\t\tAppending file [" << i_path+std::string(comp) << "]" << std::endl;
				ofile << "\n\n";
				std::ifstream ifile(i_path + std::string(comp));
				ofile << ifile.rdbuf();
				ifile.close();
			}
			ofile.close();
			std::cout << "\t\tFinished Config [" << std::string(conf["name"]) << "]" << std::endl;
		}
		std::cout << "\tFinished building Program [" << std::string(prog["name"]) << "]" << std::endl;
	}
	return true;
}
