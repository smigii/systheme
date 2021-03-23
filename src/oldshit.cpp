/*
	std::string root = "/home/smigii/.config/systheme/";

	// Print out list of themes
	std::vector<std::string> vec_themes;

	int i = 1;
	std::cout << "Please enter a theme to use:" << std::endl;
	for(const fs::directory_entry &entry : fs::directory_iterator(root + "themes/")){
		std::string theme_i = entry.path().filename().string();
		std::cout << i << ". " << theme_i << std::endl;
		vec_themes.push_back(theme_i);
		i++;
	}

	// Get user input
	std::cout << "Enter a choice between 1 and " << vec_themes.size() << ": ";
	int choice {-1};
	while(choice <= 0 || choice > vec_themes.size()){
		std::cin >> choice;
	}
	std::cout << "[" << vec_themes.at(choice - 1) << "]" << " selected." << std::endl;

	// json init
	std::ifstream ifs(root + "themes/" + vec_themes.at(choice - 1));
	json jtheme;
	ifs >> jtheme;

	// Now we build
	std::cout << "\n========== SYSTHEME 0.0.1 ==========\n";
	// Loop through the program layer...
	for(const auto &prog : jtheme){
		std::cout << "Building program [" << std::string(prog["name"]) << "]" << std::endl;
		for(const auto &conf : prog["configs"]){
			// Loop through the config file layer...
			std::cout << "\tBuilding config [" << std::string(conf["name"]) << "]" << std::endl;

			std::string o_path {conf["dest"]};

			std::ofstream trunc(o_path, std::ios::out | std::ios::trunc);
			trunc.close();

			std::ofstream ofile(o_path, std::ios::out | std::ios::app);
			std::string i_path {root + "data/" + std::string(prog["name"]) + "/" + std::string(conf["name"]) + "/" };

			std::cout << "\t\tConfig location: " + o_path << std::endl;

			for(const auto &comp : conf["components"]){
				std::cout << "\t\tAppending file [" << i_path+std::string(comp) << "]" << std::endl;
				ofile << "\n\n";
				std::ifstream ifile(i_path + std::string(comp));
				ofile << ifile.rdbuf();
				ifile.close();
			}
			ofile.close();
			std::cout << "\t\tFinished config [" << std::string(conf["name"]) << "]" << std::endl;
		}
		std::cout << "\tFinished building program [" << std::string(prog["name"]) << "]" << std::endl;
	}
	 */

	return 0;

}


void old(){
	std::string root = "/home/smigii/.config/systheme/";

	// BASH
	// Print out list of bash themes
	std::string path = root + "programs/bash/bashrc/mcomp-themes/";
	std::vector<std::string> vec_themes;

	int i = 1;
	std::cout << "Please enter a theme to use:" << std::endl;
	for(const auto &entry : fs::directory_iterator(path)){
		std::string theme_i = entry.path().filename().string();
		std::cout << i << ". " << theme_i << std::endl;
		vec_themes.push_back(theme_i);
		i++;
	}
	// Get user to select one
	std::cout << "Enter a choice between 1 and " << vec_themes.size() << ": ";
	int choice;
	while(choice <= 0 || choice > vec_themes.size()){
		std::cin >> choice;
	}

	std::cout << "[" << vec_themes.at(choice - 1) << "]" << " selected." << std::endl;

	// Overwrite .bashrc
	// Create bashrc_temp file.
	// For this example, follow BASE1 -> THEME -> PROMPT
	std::fstream file;
	std::ofstream ofile(root + "programs/bash/bashrc/out", std::ios::out | std::ios::app);

	std::ifstream ifile(root + "programs/bash/bashrc/bcomp-base1");
	ofile << ifile.rdbuf();

	std::string test = "\n\ntest.\n";
	ofile << "\n\nHELLO";

	std::ofstream("../test2.png", std::ios::binary) << std::ifstream("../test.png", std::ios::binary).rdbuf();
}