#include <iostream>

#include "exceptions.hpp"
#include "classes.hpp"

int main(int argc, char* argv[]) {

	try {

		// Initialize and validate the User and Opts objects...
		const User user = User();
		const Opts opts = Opts(argc, argv, user);

		// If initialization is succesful, we can assume the file name
		// given by the user is valid.
		PCC driver = PCC(&user, &opts);
		driver.apply_theme();

	} catch(const NoConfigDirException& e) {
		std::cout << e.msg() << "\n";
		return EXIT_FAILURE;
	} catch(const InvalidThemeException& e) {
		std::cout << e.msg() << "\n";
		return EXIT_FAILURE;
	}

	return 0;

}