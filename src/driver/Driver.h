//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_DRIVER_H
#define SYSTHEME_DRIVER_H

#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Driver {
// ----- VAR ----- //
private:
	std::string user;
	std::string root;

// ----- FNs ----- //
public:

	Driver();

	void init();

	void apply();

private:

	bool init_config_dir_prompt();

	// apply() Helper Functions
	std::string apply_io();
	json apply_init_json(const std::string& theme);
	bool apply_execute(json &theme);

};

#endif //SYSTHEME_DRIVER_H
