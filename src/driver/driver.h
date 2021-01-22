//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_DRIVER_H
#define SYSTHEME_DRIVER_H

#include <string>

class driver {
// ----- VAR ----- //
private:
	std::string user;
	std::string root;

// ----- FNs ----- //
public:

	driver();

private:

	bool init_config_prompt();

};


#endif //SYSTHEME_DRIVER_H
