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
fs::path User::home_path;

// Must be called once before being used. Stores
// the needed paths, so we don't need to keep making system
// calls.
void User::init()
{
	// Only needs to be called once.
	if(!name.empty() && !home_path.empty())
		return;

	name = getlogin();
	home_path = fs::path{"/home/" + name + "/"};

	// Check for a ~/.config directory
	if( !fs::is_directory(get_st_path()) ){
		throw NoConfigDirException(get_st_path() );
	}
}

fs::path User::get_st_path()
{
	return fs::path{home_path / ".config/systheme2/"};
}

fs::path User::expand_tilde_path(const fs::path& path)
{
	if(path.string().at(0) == '~'){
		std::string p2 = path.string().substr(2);
		return fs::path{home_path / p2};
	} else {
		return path;
	}
}

fs::path User::get_home()
{
	return fs::path{home_path};
}

fs::path User::get_data_path() {
	return fs::path{get_st_path() / "data/"};
}


/*
 * Why are we returning all these by value? Unless I'm mistaken, rvalues and RVO.
 * https://www.scribd.com/document/316704010/Want-Speed-Pass-by-Value
 */