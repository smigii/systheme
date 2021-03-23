#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#define MAX_USER_LEN 16

using json = nlohmann::json;
namespace fs = std::filesystem;

/*
 * 1. Get user ~ path
 * 2. Check if ~/.config/systheme exists
 *        - If not, prompt to create
 * 3. Get input...
 *        - CLA
 *        - Prompt
 * 3. Apply
 */

// === PROTO =============================================================

std::string get_home();

// =======================================================================

int main(int argc, char* argv[]) {

	json json;
	std::string st_path;
	std::string th_path;
	std::string dt_path;
	std::ifstream ifs_comp;
	std::ofstream ofs_write;

	st_path = "/home/";
	st_path += getlogin();
	st_path += "/.config/systheme/";

	std::cout << st_path << "\n";

	if(!fs::is_directory(st_path)){
		std::cout << "Please create the ~/.config/systheme directory.\n";
		return -1;
	}

	th_path = st_path + "themes/";

	if(argc == 2){
		th_path += argv[1];
		th_path += ".json";

		std::cout << "SELECTED THEME [" << argv[1] << "]\n";
		std::cout << "PATH [" << th_path << "]\n";

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
		std::cout << "PROGRAM [" << prog["name"] << "]\n";
		p1 = st_path + "data/";
		p1 += prog["name"];
		p1 += "/";

		for(const auto & config : prog["configs"]){
			std::cout << "\tCONFIG [" << config["name"] << "]\n";

			p2 = p1;
			p2 += config["name"];
			p2 += "/";

			std::string tmp_path = config["dest"];
			ofs_write.open(tmp_path, std::ios::trunc);
			ofs_write.close();
			ofs_write.open(tmp_path, std::ios::out | std::ios::app);

			for(const auto & component : config["components"]){
				std::cout << "\t\tCOMPONENT [" << component << "]\n";

				p3 = p2;
				p3 += component;

				std::cout << "\t\t" << p3 << "\n";
				ifs_comp.open(p3);
				ofs_write << ifs_comp.rdbuf();
				ifs_comp.close();
			}
			ofs_write.close();
		}
	}

	return 0;

}

// === FUNK ==============================================================
