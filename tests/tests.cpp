//
// Created by smigii on 2021-09-01.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/utils/user.h"
#include "../src/utils/opts.h"
#include "../src/symbolmap.h"
#include <iostream>

TEST_CASE("test")
{

	int argc_test {2};
	char* argv_test[2] = {"asd", "TEST.json"};
	User::init();
	Opts::init(argc_test, argv_test);

	systheme::make_symbol_map(Opts::get_theme_path());

	REQUIRE(1 == 1);

}