//
// Created by smigii on 2021-09-06.
//

#ifndef SYSTHEME_VERBOSITYHANDLER_H
#define SYSTHEME_VERBOSITYHANDLER_H

#include <string>

namespace opts {

	class VerbosityHandler {
	private:
		std::string indent_string;
		static std::string indent;
		bool scope_indented;

	public:
		explicit VerbosityHandler(bool indent_scope=false);
		~VerbosityHandler();
		void inc_indent();
		void dec_indent();
		void reset_indent();
		void indent_scope();

		void out_1(const std::string& msg) const;
		void out_2(const std::string& msg) const;

	};

}


#endif //SYSTHEME_VERBOSITYHANDLER_H
