//
// Created by smigii on 2021-04-03.
//

#include "classes.hpp"

#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

#include <nlohmann/json.hpp>

#include "exceptions.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

//========================================================================
//   OPTS CLASS
//========================================================================

Opts::Opts(int argc, char** argv, const User& user){

	this->argc = argc;
	this->argv = argv;

	proc_first_arg(user);
	proc_rem_args();

}

void Opts::proc_first_arg(const User& user){
	file = argv[1];
	optind++;
	std::string path = get_theme_path(user);
	struct stat buffer{};
	if(stat (path.c_str(), &buffer) != 0)
		throw InvalidThemeException(path);
}

void Opts::proc_rem_args(){
	int choice;
	while((choice = getopt(argc, argv, "svqbch")) != -1){
		switch (choice) {
			case 's':
				std::cout << "s set\n";
				opt_s = true;
				break;
			case 'v':
				std::cout << "v set\n";
				opt_v = true;
				break;
			case 'q':
				std::cout << "q set\n";
				opt_q = true;
				break;
			case 'b':
				std::cout << "b set\n";
				opt_b = true;
				break;
			case 'c':
				std::cout << "c set\n";
				opt_c = true;
				break;
			case 'h':
				HELP_ME();
				break;
			default:
				break;
		}
	}
	// Verbose takes precendence over quiet.
	if(opt_v) opt_q = false;
}

void Opts::HELP_ME(){
	std::cout << "Usage: systheme [THEME.json] [OPTION...]\n";
	std::cout << "\t-s\t\tSimulation mode, no changes are made to filesystem. Sets -v flag.\n";
	std::cout << "\t-v\t\tVerbose, prints detailed output at each step.\n";
	std::cout << "\t-q\t\tQuiet, surpress all output except error messages.\n";
	std::cout << "\t-b\t\tBackup, creates backups of all overwritten files in ~/.systheme_backups/\n";
	std::cout << "\t-c\t\tConfirm, prompts user for input before each file is overwritten.\n";
	std::cout << "\t-h\t\tHELP MEEEE\n";
}

std::string Opts::get_theme_path(const User &user) const {
	return user.get_st_root() + "themes/" + file;
}

//========================================================================
//   USER CLASS
//========================================================================

User::User(){
	name = getlogin();
	root = "/home/" + name + "/";

	if( !fs::is_directory(get_st_root()) ){
		throw NoConfigDirException( get_st_root() );
	}
}

std::string User::get_st_root() const {
	return (root + ".config/systheme/");
}

std::string User::handle_rel_path(std::string path) const {
	if(path.at(0) == '~'){
		std::string new_path = root;
		std::string p2 = path.substr(2);
		new_path += p2;
		return new_path;
	} else {
		return path;
	}
}


//========================================================================
//   PCC CLASS
//========================================================================

PCC::PCC(const User* user, const Opts* opts)
: user{user}, opts{opts} {
	// We shouldn't have to check this, since the file has been checked
	// by opts. (this feels risky af lmao)
	std::ifstream ifs(this->opts->get_theme_path(*user));
	ifs >> this->json;
}

// This should be broken up mayhaps?
void PCC::apply_theme(){

	std::ifstream ifs_comp;
	std::ofstream ofs_write;

	std::string temp_prog;
	std::string temp_conf;

	for(const auto & program : json){

		temp_prog = program["name"];
		std::cout << "\nProgram [" << temp_prog << "]...\n";

		for(const auto & config : program["configs"]){
			temp_conf = config["name"];
			std::cout << "\tOverwriting [" << temp_conf << "]...\n";

			std::string tmp_path = config["dest"];
			tmp_path = user->handle_rel_path(tmp_path);

			ofs_write.open(tmp_path, std::ios::trunc);
			ofs_write.close();
			ofs_write.open(tmp_path, std::ios::out | std::ios::app);

			for(const auto & component : config["components"]){
				std::cout << "\t\tAdding component [" << component << "]...\n";

				std::string path = user->get_st_root() + "data/" + temp_prog + "/" + temp_conf + "/" + std::string(component);

				ifs_comp.open(path);
				ofs_write << ifs_comp.rdbuf();
				ifs_comp.close();
			}
			ofs_write.close();
		}
	}

	// I dislike this
	std::cout << "\ncalling refresh.sh\n";
	std::string refresh_cmd = user->get_st_root() + "refresh.sh";
	system(refresh_cmd.c_str());
}
