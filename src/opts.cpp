//
// Created by smigii on 2021-08-29.
//

#include "opts.h"

#include <iostream>
#include <unistd.h>

#include "utils/mrworldwide.h"
#include "utils/exceptions.h"
#include "user.h"

#define INDENT_STR "|   "

int Opts::argc {-1};
char** Opts::argv {nullptr};
bool Opts::opt_s {false};
bool Opts::opt_v {false};
bool Opts::opt_V {false};
bool Opts::opt_q {false};
bool Opts::opt_b {false};
bool Opts::opt_c {false};
std::string Opts::theme;
std::string Opts::vbose_indent;

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
	if(opt_s) opt_v = true;
	// Verbose level 2 overrides verbose level 1
	if(opt_V) opt_v = true;
	// Either verbose turns off Quiet mode.
	if(opt_v || opt_V) opt_q = false;

}


void Opts::HELP_ME()
{
	std::cout << "\nsystheme version " << ST_VERSION << "\n";
	std::cout << "\nUsage: systheme [--help | --usage]\n";
	std::cout << "\nUsage: systheme [THEME] [OPTION...]\n";
	std::cout << "\t-s\tSimulation mode, no changes are made to filesystem. Sets -v flag.\n";
	std::cout << "\t-v\tVerbose, prints detailed output at each step.\n";
	std::cout << "\t-q\tQuiet, surpress all output except error messages.\n";
	std::cout << "\t-b\tBackup, creates backups of all overwritten files in ~/.systheme_backups/\n";
	std::cout << "\t-c\tConfirm, prompts user for input before each file is overwritten.\n" << std::endl;
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
	std::cout << vbose_indent << message << "\n";
}


void Opts::verbose_dummy(const std::string& message) {}


void Opts::inc_vbose_indent()
{
	vbose_indent += INDENT_STR;
}

void Opts::dec_vbose_indent()
{
	if(vbose_indent.empty())
		return;
	else
		vbose_indent = vbose_indent.substr(0, vbose_indent.length() - std::string(INDENT_STR).length());
}



