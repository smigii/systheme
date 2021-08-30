//
// Created by smigii on 2021-04-03.
//

// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE

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

	void backup_file(const std::string& file, const PCCtmp& tmp) const;
	bool prompt_confirm(PCCtmp& tmp, const std::string& dest_path) const;

	void refresh() const;

public:

	PCC(const User* user, const Opts* opts);

	void apply_theme();

};

#endif //SYSTHEME_CLASSES_HPP
