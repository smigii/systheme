//
// Created by smigii on 2021-08-29.
//

#ifndef SYSTHEME_USER_H
#define SYSTHEME_USER_H

#include <string>
//#include <filesystem>

//namespace fs = std::filesystem;

// Stores name and systheme home_path path of current user, facilitates
// any operations that rely on user specific file paths. 'Static' class
// with a private constructor, cannot be instantiated.
class User {
private:
	User();	// 'Static class', should not be able to instantiate.
	static std::string name;
	static std::string home_path;

public:
	static void init();

	// Get ~/
	[[nodiscard]] static std::string get_home();

	// Get ~/.config/systheme/
	[[nodiscard]] static std::string get_st_path();

	// Get ~/.config/systheme/data/
	[[nodiscard]] static std::string get_data_path();

	// Expand ~/* to /home/user/*
	[[nodiscard]] static std::string expand_tilde_path(std::string path);

};


#endif //SYSTHEME_USER_H
