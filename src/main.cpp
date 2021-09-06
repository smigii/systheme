#include "utils/user.h"
#include "utils/opts.h"
#include "interface.h"

#include <iostream>
#include "utils/helpers.h"
#include "utils/tokenizer.h"
#include "utils/exceptions.h"
#include "templateheader.h"

int main(int argc, char* argv[]) {

	User::init();
	Opts::init(argc, argv);
	systheme::interface::apply_system_theme(Opts::instance()->get_theme());

	Opts::shred();

	return 0;

}