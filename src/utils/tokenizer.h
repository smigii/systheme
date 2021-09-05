//
// Created by smigii on 2021-09-03.
//

#ifndef SYSTHEME_TOKENIZER_H
#define SYSTHEME_TOKENIZER_H

#include <string>
#include <vector>

namespace systheme::utils {

	class Tokenizer {

	private:
		std::string word;
		std::string delimiter;
		size_t start_idx;
		size_t end_idx;
		bool done;

		[[nodiscard]] bool idxs_npos() const;

		void update_idxs();

		void idxs_to_first_token(); // needed since we can't set size_t to negative value

	public:
		Tokenizer();
		explicit Tokenizer(std::string input, std::string delim=" \t\n\v\f\r");

		void set_string(std::string input);

		void set_delimiter(std::string delim);

		void reset();

		[[nodiscard]] std::vector<std::string> get_all_tokens();

		void add_all_tokens(std::vector<std::string>& queue);

		[[nodiscard]] std::string next_token();

		[[nodiscard]] bool is_done() const;

	};

}

#endif //SYSTHEME_TOKENIZER_H
