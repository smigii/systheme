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
	// If the first argument is --help or --usage, print the message
	// and leave. exit() is a sucky thing to do, but it's fine for now
	// since we haven't openned any files, and this IS a succesfult
	// program termination.
	if(file == "--usage" || file == "--help"){
		HELP_ME();
		exit(EXIT_SUCCESS);
	}

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
				opt_s = true;
				break;
			case 'v':
				opt_v = true;
				break;
			case 'q':
				opt_q = true;
				break;
			case 'b':
				opt_b = true;
				break;
			case 'c':
				opt_c = true;
				break;
			default:
				break;
		}
	}
	// Simulation mode activates Verbose mode.
	// Verbose Mode turns off Quiet mode.
	if(opt_s) opt_v = true;
	if(opt_v) opt_q = false;
}

void Opts::HELP_ME(){
	std::cout << "\nUsage: systheme [--help | --usage]\n";
	std::cout << "\nUsage: systheme [THEME] [OPTION...]\n";
	std::cout << "\t-s\tSimulation mode, no changes are made to filesystem. Sets -v flag.\n";
	std::cout << "\t-v\tVerbose, prints detailed output at each step.\n";
	std::cout << "\t-q\tQuiet, surpress all output except error messages.\n";
	std::cout << "\t-b\tBackup, creates backups of all overwritten files in ~/.systheme_backups/\n";
	std::cout << "\t-c\tConfirm, prompts user for input before each file is overwritten.\n";
	std::cout << "\n";
}

std::string Opts::get_theme_path(const User &user) const {
	return user.get_st_path() + "themes/" + file;
}

bool Opts::fl_s() const {return opt_s;}
bool Opts::fl_v() const{return opt_v;}
bool Opts::fl_q() const{return opt_q;}
bool Opts::fl_b() const{return opt_b;}
bool Opts::fl_c() const{return opt_c;}

std::string Opts::get_file() const {return file;}

//========================================================================
//   USER CLASS
//========================================================================

User::User(){
	name = getlogin();
	home_path = "/home/" + name + "/";

	if( !fs::is_directory(get_st_path()) ){
		throw NoConfigDirException(get_st_path() );
	}
}

std::string User::get_st_path() const {
	return (home_path + ".config/systheme/");
}

std::string User::handle_rel_path(std::string path) const {
	if(path.at(0) == '~'){
		std::string new_path = home_path;
		std::string p2 = path.substr(2);
		new_path += p2;
		return new_path;
	} else {
		return path;
	}
}

std::string User::get_home() const {
	return home_path;
}


//========================================================================
//   PCC CLASS
//========================================================================

PCC::PCC(const User* user, const Opts* opts)
: user{user}, opts{opts} {
	// We shouldn't have to check this, since the file has been checked
	// by opts. (this feels risky af lmao)
	std::ifstream ifs(this->opts->get_theme_path(*user));
	ifs >> this->js;
}

// This should be broken up mayhaps?
void PCC::apply_theme(){

	PCCtmp tmp;

	for(const auto & program : js){
		apply_prog_layer(tmp, program);
	}

	refresh();

	if(!opts->fl_q())
		std::cout << "Applied theme [" << opts->get_file() << "]\n";

	if(opts->fl_s()) {
		std::cout << "SIMULATION MODE -> NO CHANGES APPLIED\n";
	}

}

void PCC::apply_prog_layer(PCCtmp& tmp, const auto & program) const {

	tmp.prog = std::string(program["name"]);

	if(opts->fl_v())
		std::cout << "\nProgram [" << tmp.prog << "]...\n";

	for(const auto & config : program["configs"]){
		apply_conf_layer(tmp, config);
	}

}

void PCC::apply_conf_layer(PCCtmp& tmp, const auto & config) const {

	tmp.conf = config["name"];

	if(opts->fl_v())
		std::cout << "\tOverwriting [" << tmp.conf << "]...\n";

	// Get the final destination of the file we are about to overwrite
	std::string dest_path = user->handle_rel_path(std::string(config["dest"]));
	if(opts->fl_b())
		backup_file(dest_path);

	if(opts->fl_c()) {
		bool choice = prompt_confirm(tmp, dest_path);
		if(!choice)
			return;
	}

	// Clear contents of desination file (if no -s)
	if(!opts->fl_s()) {
		tmp.ofs_write.open(dest_path, std::ios::trunc);
		tmp.ofs_write.close();
		tmp.ofs_write.open(dest_path, std::ios::out | std::ios::app);
	}

	for(const auto & component : config["components"]){
		apply_comp_layer(tmp, component);
	}

	tmp.ofs_write.close();

}

void PCC::apply_comp_layer(PCCtmp& tmp, const auto & component) const {

	if(opts->fl_v())
		std::cout << "\t\tAdding component [" << component << "]...\n";

	std::string path = user->get_st_path() + "data/" + tmp.prog + "/" + tmp.conf + "/" + std::string(component);

	if(!opts->fl_s()) {
		tmp.ifs_comp.open(path);
		tmp.ofs_write << tmp.ifs_comp.rdbuf();
		tmp.ifs_comp.close();
	}

}

void PCC::refresh() const {
	if(opts->fl_v())
		std::cout << "\ncalling refresh.sh\n";

	std::string refresh_cmd = user->get_st_path() + "refresh.sh";
	// I dislike this strongly
	if(!opts->fl_s())
		system(refresh_cmd.c_str());
}

void PCC::backup_file(const std::string& file) const {
	std::string bu_path = user->get_home() + ".systheme_backups/";

	if(opts->fl_v())
		std::cout << "Backup " << file << " to " << bu_path << "\n";

	std::ifstream src(file, std::ios::binary);
	std::ofstream dst(bu_path + "hjk", std::ios::binary);
	dst << src.rdbuf();
}

bool PCC::prompt_confirm(PCCtmp &tmp, const std::string& dest_path) const {
	std::cout << "\nOverwrite...\n"
	          << "PROGRAM: " << tmp.prog << "\n"
	          << " CONFIG: " << tmp.conf << "\n"
	          << "   DEST: " << dest_path << "\n"
	          << "[y/n]: ";

	char c;
	std::cin >> c;

	while( c != 'y' && c != 'Y' && c != 'n' && c != 'N' ){
		std::cout << "[y/n]: ";
		std::cin >> c;
	}

	return (c == 'y' || c == 'Y');
}


