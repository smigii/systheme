//
// Created by smigii on 2021-08-29.
//

#include "opts.h"

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

#include "user.h"
#include "utils/exceptions.h"

Opts::Opts(int argc, char** argv){

	this->argc = argc;
	this->argv = argv;

	proc_first_arg();
	proc_rem_args();

}

void Opts::proc_first_arg(){
	if(argc < 2){
		HELP_ME();
		exit(EXIT_SUCCESS);
	}

	theme = argv[1];
	// If the first argument is --help or --usage, print the message
	// and leave. exit() is a sucky thing to do, but it's fine for now
	// since we haven't openned any files, and this IS a succesful
	// program termination.
	if(theme == "--usage" || theme == "--help"){
		HELP_ME();
		exit(EXIT_SUCCESS);
	}

	optind++;
	std::string path = get_theme_path();
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

std::string Opts::get_theme_path() const {
	return User::get_st_path() + "themes/" + theme;
}

bool Opts::fl_s() const {return opt_s;}
bool Opts::fl_v() const {return opt_v;}
bool Opts::fl_q() const {return opt_q;}
bool Opts::fl_b() const {return opt_b;}
bool Opts::fl_c() const {return opt_c;}

std::string Opts::get_theme() const {return theme;}