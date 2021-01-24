#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

#include <nlohmann/json.hpp>

#include "gui/ui.h"
#include "driver/Driver.h"
#include "tpc/Theme.h"

using json = nlohmann::json;
namespace fs = std::filesystem;

struct A{
	int x = 5;
	int y = 10;

	void set_x(int i){
		x = i;
	}

	void inc_y(int i){
		y += i;
	}

	void fn(){
		std::cout << "hello\n";
	}

	void print(){
		std::cout << "x : " << x << "\ny : " << y << std::endl;
	}
};

struct B{
	std::vector<void (A::*)()> v;
	std::vector<void (A::*)(int)> v2;
};

int test(int x, int y){
	return x*y;
}

int main() {

	A a;
	B b;

	void (A::*fnptr)(){&A::fn};
	void (A::*fnptr2)(int){&A::set_x};

	b.v.push_back(fnptr);
	b.v2.push_back(fnptr2);

	(a.*(b.v.at(0)))();

	a.print();

	(a.*(b.v2.at(0)))(69);

	a.print();

//	std::vector<int (*)(int, int)> v;
//
//	int (*fnptr)(int, int){ &test };
//
//	v.push_back(fnptr);
//
//	std::cout << v.at(0)(5, 6) << std::endl;

//	ui();

// ---------------------------------------------------------

//	Driver d;
//	try {
//		d.init();
//	} catch (std::string &e) {
//		std::cout << e << std::endl;
//	}
//	d.apply();

// ---------------------------------------------------------

//	Theme t("Theme 1");
//
//	t.add_prog("Bash");
//	t.at_prog(0)->add_conf("Bashrc", "/home/smigii/.bashrc");
//	t.at_prog(0)->at_conf(0)->add_comp("Base1");
//	t.at_prog(0)->at_conf(0)->add_comp("prompt/Minimal");
//	t.at_prog(0)->at_conf(0)->add_comp("theme/Gruvbox");
//
//	t.at_prog(0)->add_conf("Test", "/home/smigii/.test");
//	t.at_prog(0)->at_conf(1)->add_comp("Base1");
//	t.at_prog(0)->at_conf(1)->add_comp("prompt/testt");
//	t.at_prog(0)->at_conf(1)->add_comp("theme/tesssst");
//
//	t.add_prog("Vim");
//	t.at_prog(1)->add_conf(".vimrc", "/home/smigii/.vimrc");
//	t.at_prog(1)->at_conf(0)->add_comp("Base1");
//	t.at_prog(1)->at_conf(0)->add_comp("colors/Gruvbox");
//
//	std::cout << t << std::endl;

	return 0;

}