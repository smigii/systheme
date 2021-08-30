//
// Created by smigii on 2021-04-03.
//

#include "classes.hpp"

#include <iostream>
#include <filesystem>

#include "user.h"
#include "opts.h"
#include "utils/helpers.h"

namespace fs = std::filesystem;

// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE
// OBSOLETE OBSOLETE OBSOLETE OBSOLETE




//========================================================================
//   PCC CLASS
//========================================================================

PCC::PCC(const User* user, const Opts* opts)
: user{user}, opts{opts} {
	// We shouldn't have to check this, since the file has been checked
	// by opts. (this feels risky af lmao)
	std::ifstream ifs(this->opts->get_theme_path(*user));
	ifs >> this->js;
}

void PCC::apply_theme(){

	PCCtmp tmp;

	for(const auto & program : js){
		apply_prog_layer(tmp, program);
	}

	refresh();

	if(!opts->fl_q())
		std::cout << "Applied theme [" << opts->get_theme() << "]\n";

	if(opts->fl_s()) {
		std::cout << "SIMULATION MODE -> NO CHANGES APPLIED\n";
	}

}

void PCC::apply_prog_layer(PCCtmp& tmp, const auto & program) const {

	tmp.prog = std::string(program["name"]);

	if(opts->fl_v())
		std::cout << "\nProgram [" << tmp.prog << "]...\n";

	for(const auto & config : program["configs"]){
		apply_conf_layer(tmp, config);
	}

}

void PCC::apply_conf_layer(PCCtmp& tmp, const auto & config) const {

	tmp.conf = config["name"];

	if(opts->fl_v())
		std::cout << "* Config [" << tmp.conf << "]...\n";

	// Get the final destination of the file we are about to overwrite
	std::string dest_path = user->expand_tilde_path(std::string(config["dest"]));
	if(opts->fl_b())
		backup_file(dest_path, tmp);

	if(opts->fl_c()) {
		bool choice = prompt_confirm(tmp, dest_path);
		if(!choice)
			return;
	}

	// Clear contents of desination file (if no -s)
	if(!opts->fl_s()) {
		tmp.ofs_write.open(dest_path, std::ios::trunc);
		tmp.ofs_write.close();
		tmp.ofs_write.open(dest_path, std::ios::out | std::ios::app);
	}

	for(const auto & component : config["components"]){
		apply_comp_layer(tmp, component);
	}

	tmp.ofs_write.close();

}

void PCC::apply_comp_layer(PCCtmp& tmp, const auto & component) const {

	if(opts->fl_v())
		std::cout << "** Adding component [" << component << "]...\n";

	std::string path = user->get_st_path() + "data/" + tmp.prog + "/" + tmp.conf + "/" + std::string(component);

	if(!opts->fl_s()) {
		tmp.ifs_comp.open(path);
		tmp.ofs_write << tmp.ifs_comp.rdbuf();
		tmp.ifs_comp.close();
	}

}

void PCC::refresh() const {
	if(opts->fl_v())
		std::cout << "\ncalling refresh.sh\n";

	std::string refresh_cmd = user->get_st_path() + "refresh.sh";
	// I dislike this strongly
	if(!opts->fl_s())
		system(refresh_cmd.c_str());
}

void PCC::backup_file(const std::string& file, const PCCtmp& tmp) const {

	std::string new_dir = get_time_stamp();
	std::string bu_path = user->get_home() + ".systheme_backups/" + new_dir + "/";

	fs::create_directory(bu_path);

	bu_path += tmp.prog + "--";
	bu_path += fs::path(file).filename();

	if(opts->fl_v())
		std::cout << "* Backup " << file << " to " << bu_path << "\n";

	std::ifstream src(file, std::ios::binary);
	std::ofstream dst(bu_path, std::ios::binary);
	dst << src.rdbuf();
}

bool PCC::prompt_confirm(PCCtmp &tmp, const std::string& dest_path) const {
	std::cout << "\nOverwrite...\n"
	          << "PROGRAM: " << tmp.prog << "\n"
	          << " CONFIG: " << tmp.conf << "\n"
	          << "   DEST: " << dest_path << "\n"
	          << "[y/n]: ";

	char c;
	std::cin >> c;

	while( c != 'y' && c != 'Y' && c != 'n' && c != 'N' ){
		std::cout << "[y/n]: ";
		std::cin >> c;
	}

	return (c == 'y' || c == 'Y');
}


