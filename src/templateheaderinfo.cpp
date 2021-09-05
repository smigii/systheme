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


systheme::parsers::TemplateHeaderInfo::TemplateHeaderInfo(fs::path  tplate_path)
: template_path{std::move(tplate_path)}
{
	tokenize_header();
	process_tokens();
	if(destination.empty())
		throw SysthemeException("No DST directive found in template header");
}


fs::path systheme::parsers::TemplateHeaderInfo::get_dst() const
{
	return destination;
}


fs::path systheme::parsers::TemplateHeaderInfo::get_post_path() const
{
	return post_path;
}

void systheme::parsers::TemplateHeaderInfo::tokenize_header()
{
	std::ifstream ifs {template_path};
	std::string line;

	// First line
	getline(ifs, line);
	first_line_num = 2;
	systheme::utils::Tokenizer tokenizer(line);
	tokenizer.add_all_tokens(tokens);

	// Check that first token is the OPEN brace
	if(tokens.empty() || tokens.front().find(OPEN) != 0)
		throw SysthemeException("First token in template must be openning brace, (" OPEN ")\n");

	bool header_done {false};
	long offset {0};

	// Check if single line header
	header_done = check_close_token(0);

	// Get rest of tokens up to and including the %]
	while(!header_done && getline(ifs, line)){
		first_line_num++;
		offset = tokens.size();
		tokenizer.set_word(line);
		tokenizer.add_all_tokens(tokens);
		header_done = check_close_token(offset);
	}

	// Read entire file without finding CLOSE
	if(!header_done)
		throw SysthemeException("Read the entire file without finding a closing header brace (" CLOSE ")!");
}


bool systheme::parsers::TemplateHeaderInfo::check_close_token(long offset) {
	// Check if CLOSE is in line
	if (std::find(tokens.begin()+offset, tokens.end(), CLOSE) != tokens.end()) {
		// Make sure it is the last element
		if(tokens.at(tokens.size()-1) != CLOSE){
			throw SysthemeException("CLOSE (" CLOSE ") must be last token on last header line");
		}
		return true;
	}
	return false;
}


void systheme::parsers::TemplateHeaderInfo::process_tokens() {
	size_t idx {1};
	size_t size {tokens.size() - 2};

	// 2 for braces, 2 for dest directive
	if(tokens.size() < 4)
		throw SysthemeException("Template header must contain at least the destination");

	while(idx <= size) {
		std::string directive {tokens.at(idx)};
		if(directive == "DST"){
			if(idx + 1 > size)
				throw SysthemeException("DST directive requires 1 argument, 0 provided");
			destination = fs::path(User::expand_tilde_path(tokens.at(idx + 1)));
			if(!fs::exists(destination))
				throw SysthemeException("DST: invalid destination path provided: [" + destination.string() + "]");
			OPTS_VBOSE_2("template header destination path OK")
			idx += 2;
		}
		else if(directive == "POST") {
			if(idx + 1 > size)
				throw SysthemeException("POST directive requires 1 argument, 0 provided");
			post_path = fs::path(User::expand_tilde_path(tokens.at(idx + 1)));
			if(!fs::exists(post_path))
				throw SysthemeException("POST: invalid post-script path provided");
			OPTS_VBOSE_2("template post-script path OK")
			idx += 2;
		}
		else if(directive == "PRE") {
			if(idx + 1 > size)
				throw SysthemeException("PRE directive requires 1 argument, 0 provided");
			pre_path = fs::path(User::expand_tilde_path(tokens.at(idx + 1)));
			if(!fs::exists(pre_path))
				throw SysthemeException("PRE: invalid pre-script path provided");
			OPTS_VBOSE_2("template header pre-script path OK")
			idx += 2;
		}
		else {
			throw SysthemeException("Unknown directive: [" + directive + "]");
		}
	}
}

size_t systheme::parsers::TemplateHeaderInfo::get_first_line_num() const
{
	return first_line_num;
}

fs::path systheme::parsers::TemplateHeaderInfo::get_pre_path() const {
	return pre_path;
}




