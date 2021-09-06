//
// Created by smigii on 2021-08-29.
//

#ifndef SYSTHEME_OPTS_H
#define SYSTHEME_OPTS_H

#include <string>
#include <stdexcept>
#include <filesystem>
#include <memory>

namespace opts {
	class VerbosityHandler;
}

namespace fs = std::filesystem;

class User;


class Opts {

private:

	Opts();  // Use Opts::instance() to get an instance.
	static Opts* instance_ptr;

	int argc;
	char** argv;

	bool opt_s;				// Simulation mode
	bool opt_v;				// Verbose mode
	bool opt_V;				// EXTRA verbose mode (takes precedence over verbose mode)
	bool opt_b;				// Backup
	bool opt_c;				// Confirm
	std::string theme;		// Name of file theme

	void proc_first_arg();
	void proc_rem_args();
	void HELP_ME();

public:

	static void init(int argc, char** argv);
	static void shred();
	static Opts* instance();

	[[nodiscard]] bool fl_s(); // Simulation mode
	[[nodiscard]] bool fl_V(); // Extra verbose mode
	[[nodiscard]] bool fl_v(); // Verbose mode
	[[nodiscard]] bool fl_b(); // Backup mode
	[[nodiscard]] bool fl_c(); // Confirm mode

	[[nodiscard]] std::string get_theme();
	[[nodiscard]] fs::path get_theme_path();

};


class OptsException : public std::runtime_error
{
public:
	explicit OptsException(const std::string& msg)
	: std::runtime_error(msg) {}
};

#endif //SYSTHEME_OPTS_H
