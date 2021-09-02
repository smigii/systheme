//
// Created by smigii on 2021-08-29.
//

#include "opts.h"

#include <iostream>
#include <unistd.h>

#include "user.h"
#include "utils/exceptions.h"


int Opts::argc {-1};
char** Opts::argv {nullptr};
bool Opts::opt_s {false};
bool Opts::opt_v {false};
bool Opts::opt_V {false};
bool Opts::opt_q {false};
bool Opts::opt_b {false};
bool Opts::opt_c {false};
std::string Opts::theme;

void (*Opts::verbose1_ptr)(const std::string&) = Opts::verbose_dummy;
void (*Opts::verbose2_ptr)(const std::string&) = Opts::verbose_dummy;

Opts::Opts(){}


void Opts::init(int _argc, char **_argv)
{
	argc = _argc;
	argv = _argv;

	proc_first_arg();
	proc_rem_args();
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
				Opts::verbose1_ptr = &Opts::verbose_out;
				break;
			case 'V':
				opt_V = true;
				Opts::verbose1_ptr = &Opts::verbose_out;
				Opts::verbose2_ptr = &Opts::verbose_out;
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
				throw OptsException("Invalid argument: -" + std::to_string(choice));
		}
	}
	// Simulation mode activates Verbose mode.
	// Verbose Mode turns off Quiet mode.
	if(opt_s) opt_v = true;
	if(opt_v) opt_q = false;
}


void Opts::HELP_ME()
{
	std::cout << "\nUsage: systheme [--help | --usage]\n";
	std::cout << "\nUsage: systheme [THEME] [OPTION...]\n";
	std::cout << "\t-s\tSimulation mode, no changes are made to filesystem. Sets -v flag.\n";
	std::cout << "\t-v\tVerbose, prints detailed output at each step.\n";
	std::cout << "\t-q\tQuiet, surpress all output except error messages.\n";
	std::cout << "\t-b\tBackup, creates backups of all overwritten files in ~/.systheme_backups/\n";
	std::cout << "\t-c\tConfirm, prompts user for input before each file is overwritten.\n";
	std::cout << "\n";
}


fs::path Opts::get_theme_path()
{
	return fs::path{User::get_st_path() / "systhemes/" / theme};
}


bool Opts::fl_s() {return opt_s;}
bool Opts::fl_v() {return opt_v;}
bool Opts::fl_V() {return opt_V;}
bool Opts::fl_q() {return opt_q;}
bool Opts::fl_b() {return opt_b;}
bool Opts::fl_c() {return opt_c;}


std::string Opts::get_theme() {return theme;}

void Opts::verbose_out(const std::string& message)
{
	std::cout << message << "\n";
}

void Opts::verbose_dummy(const std::string& message) {}



