//
// Created by smigii on 2021-09-06.
//

#include "verbosityhandler.h"

#include <iostream>
#include "opts.h"

#define indent_str "|   "

std::string opts::VerbosityHandler::indent;

opts::VerbosityHandler::VerbosityHandler(bool _indent_scope)
: scope_indented{_indent_scope}, indent_string{indent_str}
{
	if(_indent_scope) indent_scope();
}

opts::VerbosityHandler::~VerbosityHandler()
{
	if(scope_indented)
		dec_indent();
}

void opts::VerbosityHandler::inc_indent()
{
	indent += indent_string;
}

void opts::VerbosityHandler::dec_indent()
{
	if(indent.empty())
		return;
	else
		indent = indent.substr(0, indent.length() - std::string(indent_string).length());
}

void opts::VerbosityHandler::reset_indent()
{
	indent = "";
	scope_indented = false;
}

void opts::VerbosityHandler::indent_scope()
{
	if(!scope_indented) {
		inc_indent();
		scope_indented = true;
	}
}

void opts::VerbosityHandler::out_1(const std::string &msg) const
{
	if(Opts::instance()->fl_v())
		std::cout << indent << msg << "\n";
}

void opts::VerbosityHandler::out_2(const std::string &msg) const
{
	if(Opts::instance()->fl_V())
		std::cout << indent << msg << "\n";
}
