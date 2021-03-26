#include <iostream>
#include <unistd.h>
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

// === PROTO =============================================================



// =======================================================================

class User {
private:
	std::string name;
	std::string root;

	std::string prog;
	std::string conf;
	std::string comp;

	std::string path;

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

	std::string convert_rel_path(std::string path){
		if(path.at(0) == '~'){
			std::string new_path = root;
			std::string p2 = path.substr(2);
			new_path += p2;
			return new_path;
		} else {
			return path;
		}
	}

};

int main(int argc, char* argv[]) {

	json json;
	std::string st_path;
	std::string th_path;
	std::string dt_path;
	std::ifstream ifs_comp;
	std::ofstream ofs_write;

	User usr = User();
	st_path += usr.get_root() + "/.config/systheme/";

	std::cout << "SYSTHEME 0.0.2\n\n";

	if(!fs::is_directory(st_path)){
		std::cout << "Please create the ~/.config/systheme directory.\n";
		return -1;
	}

	th_path = st_path + "themes/";

	if(argc == 2){
		th_path += argv[1];
		th_path += ".json";

		std::cout << "SELECTED THEME [" << argv[1] << "]\n";

		std::ifstream ifs(th_path);
		if(ifs.good()){
			ifs >> json;
		} else {
			std::cout << "INVALID FILE\n";
		}
	} else {
		std::cout << "FUCK YOU\n";
		return -1;
	}


	std::string p1, p2, p3;
	for(const auto & prog : json){
		std::cout << "\nProgram [" << prog["name"] << "]...\n";
		p1 = st_path + "data/";
		p1 += prog["name"];
		p1 += "/";

		for(const auto & config : prog["configs"]){
			std::cout << "\tOverwriting [" << config["name"] << "]...\n";

			p2 = p1;
			p2 += config["name"];
			p2 += "/";

			std::string tmp_path = config["dest"];
			tmp_path = usr.convert_rel_path(tmp_path);

			ofs_write.open(tmp_path, std::ios::trunc);
			ofs_write.close();
			ofs_write.open(tmp_path, std::ios::out | std::ios::app);

			for(const auto & component : config["components"]){
				std::cout << "\t\tAdding component [" << component << "]...\n";

				p3 = p2;
				p3 += component;

				ifs_comp.open(p3);
				ofs_write << ifs_comp.rdbuf();
				ifs_comp.close();
			}
			ofs_write.close();
		}
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
