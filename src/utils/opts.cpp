//
// Created by smigii on 2021-08-29.
//

#include "opts.h"

#include <iostream>
#include <unistd.h>

#include "mrworldwide.h"
#include "exceptions.h"
#include "user.h"

Opts* Opts::instance_ptr {nullptr};

Opts::Opts() = default;

void Opts::init(int _argc, char **_argv)
{
	if(Opts::instance_ptr)
		return;
	else
		Opts::instance_ptr = new Opts;

	instance_ptr->argc = _argc;
	instance_ptr->argv = _argv;
	instance_ptr->opt_s = false;

	instance_ptr->opt_v = false;
	instance_ptr->opt_V = false;
	instance_ptr->opt_b = false;
	instance_ptr->opt_c = false;

	instance_ptr->proc_first_arg();
	instance_ptr->proc_rem_args();
}

void Opts::shred()
{
	delete instance_ptr;
	instance_ptr = nullptr;
}

Opts *Opts::instance()
{
	return instance_ptr;
}

void Opts::proc_first_arg()
{
	if(argc < 2){
		HELP_ME();
		exit(EXIT_SUCCESS);
	}

	// If the first argument is --help or --usage, print the message
	// and leave. exit() is a sucky thing to do, but it's fine for now
	// since we haven't openned any files, and this IS a succesful
	// program termination.
	theme = argv[1];
	if(theme == "--usage" || theme == "--help"){
		HELP_ME();
		exit(EXIT_SUCCESS);
	} else if(theme == "-v" || theme == "--version") {
		std::cout << "v" << ST_VERSION << std::endl;
		exit(EXIT_SUCCESS);
	}

	optind++;
	std::string path = get_theme_path();
	if(!fs::exists(path))
		throw OptsException("Invalid theme path: " + path);
}

void Opts::proc_rem_args()
{
	int choice;
	while((choice = getopt(argc, argv, "svVqbch")) != -1){
		switch (choice) {
			case 's':
				opt_s = true;
				break;
			case 'v':
				opt_v = true;
				break;
			case 'V':
				opt_V = true;
				break;
			case 'b':
				opt_b = true;
				break;
			case 'c':
				opt_c = true;
				break;
			default:
				throw OptsException("Invalid argument: -" + std::to_string(choice));
		}
	}
	// Simulation mode activates Verbose mode.
	if(opt_s) opt_v = true;
	// Verbose level 2 overrides verbose level 1
	if(opt_V) opt_v = true;

}

void Opts::HELP_ME()
{
	std::cout << "\nsystheme version " << ST_VERSION << "\n";
	std::cout << "\nUsage: systheme [--help | --usage]\n";
	std::cout << "\nUsage: systheme [THEME] [OPTION...]\n";
	std::cout << "\t-s\tSimulation mode, no changes are made to filesystem. Sets -v flag.\n";
	std::cout << "\t-v\tVerbose, prints detailed output at each step.\n";
	std::cout << "\t-V\tExtra verbose, prints more detailed output at each step.\n";
	std::cout << "\t-b\tBackup, creates backups of all overwritten files in ~/.systheme_backups/\n";
	std::cout << "\t-c\tConfirm, prompts user for input before each file is overwritten.\n" << std::endl;
}

fs::path Opts::get_theme_path() { return fs::path{User::get_st_path() / "systhemes/" / theme}; }
std::string Opts::get_theme() {return theme;}

bool Opts::fl_s() {return opt_s;}
bool Opts::fl_v() {return opt_v;}
bool Opts::fl_V() {return opt_V;}
bool Opts::fl_b() {return opt_b;}
bool Opts::fl_c() {return opt_c;}








