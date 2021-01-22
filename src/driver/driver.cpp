//
// Created by smigii on 2021-01-21.
//

/* ================================================================================================
 * TODO:
 * 		getlogin() will not work on daemonized processes. Will need handle for that.
 * ================================================================================================ */

#include "driver.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <stdexcept>
#include <unistd.h>		// getlogin_r()

driver::driver()
: root{""} {
	// Get the user
	char* c_user;
	if(getlogin_r(c_user, 16) == 0){
		user = c_user;
	} else {
		std::string msg = "\tFailed to get user login name using getlogin_r(char* name, size_t bufsize).";
		throw std::runtime_error(msg);
	}

	// Check that there is a /home/USER directory
	if(!std::filesystem::is_directory("/home/" + user)){
		std::string msg = "\tDirectory does not exist : [/home/" + user + "/]";
		throw std::runtime_error(msg);
	}

	// Check that there is a /home/USER/.config/systheme directory
	// If there isn't, prompt user to create one. Creation should be handled by a setup script
	// Set the "root" attr to "/home/USER/.config/systheme"
	if(!std::filesystem::is_directory("/home/" + user + "/.config/systheme/") && !init_config_prompt()){
		std::string msg {
			"\tDirectory does not exist : /home/" + user + "/.config/systheme/\n" +
			"\tPlease create this directory before continuing."
		};
		throw std::runtime_error(msg);
	} else {
		root = "/home/" + user + "/.config/systheme/";
	}
}

// Prompts user to create the ~/.config/systheme directory.
// Returns true if created, false if denied.
bool driver::init_config_prompt() {
	std::cout << "Directory not found : [~/.config/systheme/]\n\tWould you like to create it now?\n";
	char c {'0'};
	do{
		std::cout << "\t[y/n] : ";
		std::cin >> c;
	} while(c != 'y' && c != 'n');

	if(c == 'y') {
		if(!std::filesystem::is_directory("/home/" + user + "/.config")){
			std::filesystem::create_directory("/home/" + user + "/.config/");
		}
		std::filesystem::create_directory("/home/" + user + "/.config/systheme/");
		return true;
	} else {
		return false;
	}
}
