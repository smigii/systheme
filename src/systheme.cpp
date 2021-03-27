#include <iostream>
#include <unistd.h>
#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

/*
 * SHIT TO ADD
 *     - Some kind of auto backup directory in .config/systheme
 *     - Individual level setting
 *       (i.e. set prompt without changing anything else)
 *     - Command line options
 *           - verbosity
 *           - debug mode
 */

using json = nlohmann::json;
namespace fs = std::filesystem;

// === TD & E =============================================================



// =======================================================================

// === PROTO =============================================================



// =======================================================================

class User {
private:
	std::string name;
	std::string root;

public:
	User(){
		name = getlogin();
		root = "/home/" + name + "/";
	}

	std::string get_name(){
		return name;
	}

	std::string get_root(){
		return root;
	}

	std::string get_st_root(){
		return root + ".config/systheme/";
	}

	std::string handle_rel_path(std::string path){
		if(path.at(0) == '~'){
			std::string new_path = root;
			std::string p2 = path.substr(2);
			new_path += p2;
			return new_path;
		} else {
			return path;
		}
	}

	in x;

};

class PCC {
private:
	std::string prog;
	std::string conf;

public:
	void set_prog(std::string _prog) {
		this->prog = std::move(_prog);
		conf = nullptr;
	}

	void set_conf(std::string _conf){
		this->conf = std::move(_conf);
	}

	void apply_theme(const json& _json, User usr){

		std::ifstream ifs_comp;
		std::ofstream ofs_write;

		for(const auto & program : _json){

			set_prog(program["name"]);
			std::cout << "\nProgram [" << this->prog << "]...\n";

			for(const auto & config : program["configs"]){
				set_conf(config["name"]);
				std::cout << "\tOverwriting [" << this->conf << "]...\n";

				std::string tmp_path = config["dest"];
				tmp_path = usr.handle_rel_path(tmp_path);

				ofs_write.open(tmp_path, std::ios::trunc);
				ofs_write.close();
				ofs_write.open(tmp_path, std::ios::out | std::ios::app);

				for(const auto & component : config["components"]){
					std::cout << "\t\tAdding component [" << component << "]...\n";

					std::string path = usr.get_st_root() + "data/" + prog + "/" + conf + "/" + component;

					ifs_comp.open(path);
					ofs_write << ifs_comp.rdbuf();
					ifs_comp.close();
				}
				ofs_write.close();
			}
		}
	}
};



// === MAIN ==============================================================

int main(int argc, char* argv[]) {

	json json;
	std::string st_path;
	std::string th_path;
	std::string dt_path;
	std::ifstream ifs_comp;
	std::ofstream ofs_write;

	User usr = User();

	std::cout << "SYSTHEME 0.0.3\n\n";

	if(!fs::is_directory(usr.get_st_root())){
		std::cout << "Please create the ~/.config/systheme directory.\n";
		return -1;
	}

	if(argc == 2){
		th_path += argv[1];
		th_path += ".json";

		std::cout << "SELECTED THEME [" << argv[1] << "]\n";

		std::ifstream ifs(usr.get_st_root() + "themes/");
		if(ifs.good()){
			ifs >> json;
		} else {
			std::cout << "INVALID FILE\n";
		}
	} else {
		std::cout << "NO FUCK YOU\n";
		return -1;
	}


	std::cout << "\nDone building theme [" << argv[1] << "]\n";

	// This isn't the WORST thing in the world
	// since none of the users input ends up
	// here, but fuck the system()
	std::cout << "\ncalling refresh.sh\n";
	std::string refresh_cmd = st_path + "refresh.sh";
	system(refresh_cmd.c_str());

	return 0;

}

// === FUNK ==============================================================
