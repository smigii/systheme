#include "user.h"
#include "opts.h"
#include "engine.h"

#include <iostream>
#include "utils/helpers.h"
#include "utils/tokenizer.h"
#include "utils/exceptions.h"
#include "templateheaderinfo.h"

int main(int argc, char* argv[]) {

	User::init();
	Opts::init(argc, argv);
	systheme::apply_system_theme(Opts::get_theme());


//	fs::path p {User::get_data_path() / "testing/template"};
//	try {
//		systheme::parsers::TemplateHeaderInfo thi(p);
//		std::cout << thi.get_dst().string() << std::endl;
//		std::cout << thi.get_post_path().string() << std::endl;
//		std::cout << thi.get_pre_path().string() << std::endl;
//		std::cout << thi.get_first_line_num() << std::endl;
//	} catch(const SysthemeException& e){
//		std::cout << e.msg();
//	}


	return 0;

}