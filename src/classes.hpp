//
// Created by smigii on 2021-04-03.
//

#ifndef SYSTHEME_CLASSES_HPP
#define SYSTHEME_CLASSES_HPP

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Classes ===============================================================
class Opts;
class User;
class PCC;
struct PCCtmp;
// Classes ===============================================================

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
	std::string file;   // Name of file theme

	void proc_first_arg(const User& user);

	void proc_rem_args();

	void HELP_ME();

public:
	Opts(int argc, char** argv, const User& user);

	[[nodiscard]] bool fl_s() const;
	[[nodiscard]] bool fl_v() const;
	[[nodiscard]] bool fl_q() const;
	[[nodiscard]] bool fl_b() const;
	[[nodiscard]] bool fl_c() const;

	[[nodiscard]] std::string get_file() const;

	[[nodiscard]] std::string get_theme_path(const User& user) const;

};

// User Class
// Stores name and systheme home_path path of current user, facilitates
// any operations that rely on user specific file paths.
class User {
private:
	std::string name;
	std::string home_path;

public:
	User();

	[[nodiscard]] std::string get_home() const;

	[[nodiscard]] std::string get_st_path() const ;

	[[nodiscard]] std::string handle_rel_path(std::string path) const ;

};

// Temp data struct that holds data to be modified during execution
// of PCC.apply_theme()
struct PCCtmp {
	std::string prog;
	std::string conf;
	std::ifstream ifs_comp;
	std::ofstream ofs_write;
};

// Program / Config / Class
// This class uses the User and Opts class to build and overwrite
// the desired files.
class PCC {
private:

	const User* user;
	const Opts* opts;
	json js;

	void apply_prog_layer(PCCtmp& tmp, const auto & program) const;
	void apply_conf_layer(PCCtmp& tmp, const auto & config) const;
	void apply_comp_layer(PCCtmp& tmp, const auto & component) const;

	void backup_file(const std::string& file) const;
	bool prompt_confirm(PCCtmp& tmp, const std::string& dest_path) const;

	void refresh() const;

public:

	PCC(const User* user, const Opts* opts);

	void apply_theme();

};

#endif //SYSTHEME_CLASSES_HPP
