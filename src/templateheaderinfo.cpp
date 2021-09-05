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
#include "opts.h"
#include "user.h"

#define COMMENT "#"
#define DESTINATION "DST"
#define POST_SCRIPT "POST"
#define PRE_SCRIPT "PRE"


systheme::parsers::TemplateHeaderInfo::TemplateHeaderInfo(fs::path  tplate_path)
: template_path{std::move(tplate_path)}
{
	std::vector<std::string> tokens;
	std::ifstream ifs {template_path};
	std::string line;

	// First line
	getline(ifs, line);
	first_line_num = 2;
	systheme::utils::Tokenizer tokenizer(line);
	tokenizer.add_all_tokens(tokens);

	// Check that first token is the OPEN brace
	if(tokens.size() != 1 || tokens.front() != OPEN)
		throw SysthemeException("First token in template must be openning an brace, (" OPEN ")\n");

	bool header_done {false};

	// Get rest of tokens up to and including the %]
	while(!header_done && getline(ifs, line)){
		first_line_num++;
		tokenizer.set_string(line);
		tokens = tokenizer.get_all_tokens();
		header_done = process_tokens(tokens);
	}

	// Read entire file without finding CLOSE
	if(!header_done)
		throw SysthemeException("Read the entire file without finding a closing header brace (" CLOSE ")!");

	if(destination.empty())
		throw SysthemeException("Template header must include DST directive");

}


bool systheme::parsers::TemplateHeaderInfo::process_tokens(const std::vector<std::string>& tokens) {

	// Empty line
	if(tokens.empty())
		return false;

	std::string directive {tokens.front()};
	size_t argc {tokens.size()};

	if(directive == "#"){}

	else if(directive == DESTINATION){
		if(argc != 2)
			throw SysthemeException(DESTINATION " directive requires 1 argument, " + std::to_string(argc - 1) + " provided");
		destination = fs::path(User::expand_tilde_path(tokens.at(1)));
		if(!fs::exists(destination))
			throw SysthemeException(DESTINATION ": invalid destination path provided: [" + destination.string() + "]");
		OPTS_VBOSE_2("template header destination path OK")
	}
	else if(directive == POST_SCRIPT) {
		if(argc != 2)
			throw SysthemeException(POST_SCRIPT " directive requires 1 argument, " + std::to_string(argc - 1) + " provided");
		post_path = fs::path(User::expand_tilde_path(tokens.at(1)));
		if(!fs::exists(post_path))
			throw SysthemeException(POST_SCRIPT ": invalid post-script path provided");
		OPTS_VBOSE_2("template post-script path OK")
	}
	else if(directive == PRE_SCRIPT) {
		if(argc != 2)
			throw SysthemeException(PRE_SCRIPT " directive requires 1 argument, " + std::to_string(argc - 1) + " provided");
		pre_path = fs::path(User::expand_tilde_path(tokens.at(1)));
		if(!fs::exists(pre_path))
			throw SysthemeException(PRE_SCRIPT": invalid pre-script path provided");
		OPTS_VBOSE_2("template header pre-script path OK")
	}
	else if(directive == CLOSE) {
		if(argc != 1)
			throw SysthemeException("Closing brace must be only token in line");
		return true;
	}
	else {
		throw SysthemeException("Unknown directive: [" + directive + "]");
	}

	return false;
}


fs::path systheme::parsers::TemplateHeaderInfo::get_dst() const
{
	return destination;
}


fs::path systheme::parsers::TemplateHeaderInfo::get_post_path() const
{
	return post_path;
}


size_t systheme::parsers::TemplateHeaderInfo::get_first_line_num() const
{
	return first_line_num;
}


fs::path systheme::parsers::TemplateHeaderInfo::get_pre_path() const {
	return pre_path;
}




