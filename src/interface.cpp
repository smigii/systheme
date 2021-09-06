//
// Created by smigii on 2021-08-29.
//

#include "interface.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>

#include "utils/exceptions.h"
#include "opts.h"
#include "templateparser.h"

namespace fs = std::filesystem;

using json = nlohmann::json;

// --------------------------------------------------------------
// --- PROTOTYPES -----------------------------------------------

bool prompt_abort();

// --------------------------------------------------------------
// --- FHANDLE --------------------------------------------------

void systheme::interface::apply_program_theme(const std::string& program, const std::string& theme)
{
	std::string string {program + "::" + theme};
	OPTS_VBOSE_1("\nprocessing [" + string + "]")
	systheme::opts::VerboseIndentScope vis;

	try{ systheme::templates::process_template(program, theme); }
	catch(const SysthemeException& e) {
		throw SysthemeException("Error processing program: [" + string + "]\n" + e.msg());
	}

}


void systheme::interface::apply_system_theme(const std::string& theme)
{
	json derulo;
	std::ifstream ifs(Opts::get_theme_path());
	std::vector<std::string> errors;
	ifs >> derulo;

	for(const auto& kvp : derulo.items()){
		const std::string& program {kvp.key()};
		const std::string& conf_theme {kvp.value()};
		try{ apply_program_theme(program, conf_theme); }
		catch(const SysthemeException& e) {
			std::string id {"*ERROR: program [" + program + "], theme [" + conf_theme + "]\n"};
			OPTS_VBOSE_1("\n" + id + e.msg())
			errors.push_back(id);
			if (prompt_abort()) {exit(-1);}
		}
	}

	if(!errors.empty()){
		OPTS_VBOSE_1("\nERROR REPORT:")
		for(const std::string& err : errors)
			std::cout << err << "\n\n";
	}
}

// --------------------------------------------------------------
// --- IMPLEMENTATIONS ------------------------------------------

bool prompt_abort()
{
	std::cout << "\nWould you like to abort, or proceed to next config?" << std::endl;

	char c {0};

	while( c != 'a' && c != 'A' && c != 'p' && c != 'P' ){
		std::cout << "[A/a]bort, [P/p]roceed: ";
		std::cin >> c;
	}

	return (c == 'a' || c == 'A');
}