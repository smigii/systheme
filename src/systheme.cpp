#include "user.h"
#include "opts.h"
#include "interface.h"

#include <iostream>
#include "utils/helpers.h"
#include "utils/tokenizer.h"
#include "utils/exceptions.h"
#include "templateheaderinfo.h"

int main(int argc, char* argv[]) {

	User::init();
	Opts::init(argc, argv);
	systheme::interface::apply_system_theme(Opts::get_theme());

	return 0;

}