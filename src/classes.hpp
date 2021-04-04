//
// Created by smigii on 2021-04-03.
//

#ifndef SYSTHEME_CLASSES_HPP
#define SYSTHEME_CLASSES_HPP

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Classes ===============================================================
class Opts;
class User;
class PCC;
// Classes ===============================================================

// Opts Class
// Stores the CLA flags that are set by user, and the theme file to use.
class Opts {
private:
	int argc;
	char** argv;

	bool opt_s = false;     // Simulation mode
	bool opt_v = false;     // Verbose (takes precedence over Quiet option)
	bool opt_q = false;     // Quiet
	bool opt_b = false;     // Backup
	bool opt_c = false;     // Confirm
	std::string file;   // Name of file theme

	void proc_first_arg(const User& user);

	void proc_rem_args();

	void HELP_ME();

public:
	Opts(int argc, char** argv, const User& user);

	[[nodiscard]] std::string get_theme_path(const User& user) const;

};

// User Class
// Stores name and systheme root path of current user, facilitates
// any operations that rely on user specific file paths.
class User {
private:
	std::string name;
	std::string root;

public:
	User();

	[[nodiscard]] std::string get_st_root() const ;

	[[nodiscard]] std::string handle_rel_path(std::string path) const ;

};

// Program / Config / Class
// This class uses the User and Opts class to build and overwrite
// the desired files.
class PCC {
private:

	const User* user;
	const Opts* opts;
	json json;

public:
	PCC(const User* user, const Opts* opts);

	void apply_theme();

};

#endif //SYSTHEME_CLASSES_HPP
