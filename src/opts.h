//
// Created by smigii on 2021-08-29.
//

#ifndef SYSTHEME_OPTS_H
#define SYSTHEME_OPTS_H

#include <string>

class User;

// Opts Class
// Stores the CLA flags that are set by user, and the theme file to use.
class Opts {

private:
	int argc;
	char** argv;

	bool opt_s = false;     // Simulation mode
	bool opt_v = false;     // Verbose mode (takes precedence over Quiet option)
	bool opt_q = false;     // Quiet mode
	bool opt_b = false;     // Backup
	bool opt_c = false;     // Confirm
	std::string theme;       // Name of file theme

	void proc_first_arg();

	void proc_rem_args();

	void HELP_ME();

public:
	Opts(int argc, char** argv);

	[[nodiscard]] bool fl_s() const;
	[[nodiscard]] bool fl_v() const;
	[[nodiscard]] bool fl_q() const;
	[[nodiscard]] bool fl_b() const;
	[[nodiscard]] bool fl_c() const;

	[[nodiscard]] std::string get_theme() const;

	[[nodiscard]] std::string get_theme_path() const;

};

#endif //SYSTHEME_OPTS_H
