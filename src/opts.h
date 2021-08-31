//
// Created by smigii on 2021-08-29.
//

#ifndef SYSTHEME_OPTS_H
#define SYSTHEME_OPTS_H

#include <string>
#include <stdexcept>
#include <filesystem>

#define IF_VERBOSE(out) if(Opts::fl_v()) std::cout << out;
#define IF_VERBOSE_ENDL(out) if(Opts::fl_v()) std::cout << out << std::endl;

namespace fs = std::filesystem;

class User;

// Opts Class
// Stores the CLA flags that are set by user, and the theme file to use.
class Opts {

private:

	Opts();  // "static" class

	static int argc;
	static char** argv;

	static bool opt_s;				// Simulation mode
	static bool opt_v;				// Verbose mode (takes precedence over Quiet option)
	static bool opt_q;				// Quiet mode
	static bool opt_b;				// Backup
	static bool opt_c;				// Confirm
	static std::string theme;		// Name of file theme

	static void proc_first_arg();
	static void proc_rem_args();
	static void HELP_ME();

public:

	static void init(int argc, char** argv);

	[[nodiscard]] static bool fl_s(); // Simulation mode
	[[nodiscard]] static bool fl_v(); // Verbose mode
	[[nodiscard]] static bool fl_q(); // Quiet mode
	[[nodiscard]] static bool fl_b(); // Backup mode
	[[nodiscard]] static bool fl_c(); // Confirm mode

	[[nodiscard]] static std::string get_theme();
	[[nodiscard]] static fs::path get_theme_path();

};

class OptsException : public std::runtime_error
{
public:
	OptsException(const std::string& msg)
	: std::runtime_error(msg) {}
};

#endif //SYSTHEME_OPTS_H
