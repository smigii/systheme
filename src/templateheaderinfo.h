//
// Created by smigii on 2021-09-03.
//

#ifndef SYSTHEME_TEMPLATEHEADERINFO_H
#define SYSTHEME_TEMPLATEHEADERINFO_H

#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

namespace systheme::parsers {

	class TemplateHeaderInfo {

	private:
		const fs::path template_path;

		fs::path destination;
		fs::path post_path;
		fs::path pre_path;
		size_t first_line_num;

		[[nodiscard]] bool process_tokens(const std::vector<std::string>& tokens);

	public:
		explicit TemplateHeaderInfo(fs::path tplate_path);

		[[nodiscard]] fs::path get_dst() const;
		[[nodiscard]] fs::path get_post_path() const;
		[[nodiscard]] fs::path get_pre_path() const;
		[[nodiscard]] size_t get_first_line_num() const;

	};

}


#endif //SYSTHEME_TEMPLATEHEADERINFO_H
