//
// Created by smigii on 2021-08-29.
//

#ifndef SYSTHEME_OPTS_H
#define SYSTHEME_OPTS_H

#include <string>
#include <stdexcept>
#include <filesystem>

#define OPTS_VBOSE_1(msg) Opts::verbose1_ptr(msg);
#define OPTS_VBOSE_2(msg) Opts::verbose2_ptr(msg);

namespace fs = std::filesystem;

class User;


class Opts {

private:

	Opts();  // "static" class

	static int argc;
	static char** argv;

	static bool opt_s;				// Simulation mode
	static bool opt_v;				// Verbose mode (takes precedence over quiet mode)
	static bool opt_V;				// EXTRA verbose mode (takes precedence over verbose mode)
	static bool opt_q;				// Quiet mode
	static bool opt_b;				// Backup
	static bool opt_c;				// Confirm
	static std::string theme;		// Name of file theme

	static std::string vbose_indent;

	static void proc_first_arg();
	static void proc_rem_args();
	static void HELP_ME();

	static void verbose_out(const std::string& message);
	static void verbose_dummy(const std::string& message);

public:

	static void init(int argc, char** argv);

	[[nodiscard]] static bool fl_s(); // Simulation mode
	[[nodiscard]] static bool fl_V(); // Extra verbose mode
	[[nodiscard]] static bool fl_v(); // Verbose mode
	[[nodiscard]] static bool fl_q(); // Quiet mode
	[[nodiscard]] static bool fl_b(); // Backup mode
	[[nodiscard]] static bool fl_c(); // Confirm mode

	[[nodiscard]] static std::string get_theme();
	[[nodiscard]] static fs::path get_theme_path();

	static void (*verbose1_ptr)(const std::string&);
	static void (*verbose2_ptr)(const std::string&);

	static void inc_vbose_indent();
	static void dec_vbose_indent();

};

// Increases verbosity indent upon creation,
// decreases indent when out of scope.
namespace systheme::opts {
	struct VerboseIndentScope {
		VerboseIndentScope() {
			Opts::inc_vbose_indent();
		}

		~VerboseIndentScope() {
			Opts::dec_vbose_indent();
		}
	};
}

class OptsException : public std::runtime_error
{
public:
	OptsException(const std::string& msg)
	: std::runtime_error(msg) {}
};

#endif //SYSTHEME_OPTS_H
