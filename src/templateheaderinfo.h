//
// Created by smigii on 2021-09-03.
//

#ifndef SYSTHEME_TEMPLATEHEADERINFO_H
#define SYSTHEME_TEMPLATEHEADERINFO_H

#include <queue>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace systheme::parsers {

	class TemplateHeaderInfo {

	private:
		const fs::path template_path;
		fs::path destination;
		fs::path script_path;
		int first_line {-1};
		std::queue<std::string> tokens;

		bool file_done{false};
		bool header_done {false};

		void process_current_tokens();

		std::string get_next_tokens();

	public:
		TemplateHeaderInfo(fs::path tplate_path);

		[[nodiscard]] fs::path get_dst() const;
		[[nodiscard]] fs::path get_script_path() const;

	};

}


#endif //SYSTHEME_TEMPLATEHEADERINFO_H
