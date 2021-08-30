//
// Created by smigii on 2021-08-29.
//

#include "user.h"

#include <unistd.h>
#include <filesystem>

#include "utils/exceptions.h"

namespace fs = std::filesystem;

// Initialize static vars
std::string User::name;
std::string User::home_path;

// Must be called once before being used. Stores
// the needed paths, so we don't need to keep making system
// calls.
void User::init()
{
	// Only needs to be called once.
	if(!name.empty() && !home_path.empty())
		return;

	name = getlogin();
	home_path = "/home/" + name + "/";

	if( !fs::is_directory(get_st_path()) ){
		throw NoConfigDirException(get_st_path() );
	}
}

std::string User::get_st_path()
{
	return (home_path + ".config/systheme2/");
}

std::string User::expand_tilde_path(std::string path)
{
	if(path.at(0) == '~'){
		std::string new_path = home_path;
		std::string p2 = path.substr(2);
		new_path += p2;
		return new_path;
	} else {
		return path;
	}
}

std::string User::get_home()
{
	return home_path;
}

std::string User::get_data_path() {
	return get_st_path() + "data/";
}


