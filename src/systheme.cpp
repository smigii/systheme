#include "user.h"
#include "opts.h"
#include "engine.h"

#include <iostream>
#include "utils/helpers.h"
#include "utils/tokenizer.h"

int main(int argc, char* argv[]) {

	User::init();
	Opts::init(argc, argv);
//	systheme::apply_system_theme(Opts::get_theme());



	return 0;

}