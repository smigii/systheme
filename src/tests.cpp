//
// Created by smigii on 2021-04-03.
//

#include <iostream>

#include "exceptions.hpp"
#include "classes.hpp"

void test_user();
void test_opts();
void test_pcc();

int main(int argc, char** argv){
//	test_user();
	test_opts();
}

void test_user(){
	try {

		const User user = User();
		std::cout << user.get_st_root() << "\n";

	} catch(const NoConfigDirException& e) {

		std::cout << e.msg() << "\n";
		exit(EXIT_FAILURE);

	}
}

void test_opts(){
	try{

		int argc = 3;
		char* argv[] = {"__NAME__", "gruvbox.json", "-svqbch"};

		const User user = User();
		const Opts opts = Opts(argc, argv, user.get_st_root());

	} catch(const InvalidThemeException& e) {

		std::cout << e.msg() << "\n";
		exit(EXIT_FAILURE);

	}

}

