//
// Created by smigii on 2021-09-03.
//

#include "templateheaderinfo.h"

#include <utility>
#include <string>
#include <fstream>

#include "utils/tokenizer.h"
#include "utils/exceptions.h"
#include "utils/mrworldwide.h"


/*
 * ALGORITHM
 *
 * 1. Read first line of file, ensure the first token is OPEN brace
 * 2. Check if first line of tokens contained CLOSE brace
 * 3. If not, continue reading lines until we see a CLOSE brace.
 * 4. Once found, ensure it is the last token on that line.
 * 5. Set line_num to the next line.
 *
 */


systheme::parsers::TemplateHeaderInfo::TemplateHeaderInfo(fs::path tplate_path)
: template_path{std::move(tplate_path)}
{
	std::ifstream ifs {tplate_path};
	std::string line;
	getline(ifs, line);
	systheme::utils::Tokenizer tokenizer(line);

	tokenizer.add_all_tokens(tokens);

	// Check that first token is the OPEN brace
	if(tokens.empty() || tokens.front() != OPEN)
		throw SysthemeException("First token in template must be openning brace, (" OPEN ")\n");
	tokens.pop();



	// Finish rest of line
	process_current_tokens();

	while(!header_done && getline(ifs, line)){
		getline(ifs, line);
		tokenizer.set_word(line);
		tokenizer.add_all_tokens(tokens);
		process_current_tokens();
	}

	if(!header_done)
		throw SysthemeException("Read the entire file without finding a closing header brace (" DELIM ")!");

}


fs::path systheme::parsers::TemplateHeaderInfo::get_dst() const
{
	return destination;
}


fs::path systheme::parsers::TemplateHeaderInfo::get_script_path() const
{
	return script_path;
}


void systheme::parsers::TemplateHeaderInfo::process_current_tokens()
{
	while(!tokens.empty()){

		std::string directive {tokens.front()};
		tokens.pop();

		if(directive == "DST"){
			if(tokens.empty())
				throw SysthemeException("DST directive requires 1 argument, 0 provided");
			destination = fs::path(tokens.front());
			tokens.pop();
		}
		else if(directive == "SH"){
			if(tokens.empty())
				throw SysthemeException("SH directive requires 1 argument, 0 provided");
			script_path = fs::path(tokens.front());
			tokens.pop();
		}
		else {
			throw SysthemeException("Unknown directive: [" + directive + "]");
		}

	}
}


std::string systheme::parsers::TemplateHeaderInfo::get_next_tokens()
{

}



