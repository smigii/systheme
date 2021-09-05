//
// Created by smigii on 2021-09-03.
//

#include "tokenizer.h"

systheme::utils::Tokenizer::Tokenizer()
: Tokenizer("") {}


systheme::utils::Tokenizer::Tokenizer(std::string input, std::string delim)
: word{std::move(input)}, delimiter{std::move(delim)}, done{false}
{
	idxs_to_first_token();
}


std::vector<std::string> systheme::utils::Tokenizer::get_all_tokens()
{
	std::vector<std::string> result;
	add_all_tokens(result);
	return result;
}


std::string systheme::utils::Tokenizer::next_token()
{
	if(is_done()) {
		done = true;
		return "";
	}

	std::string result {word.substr(start_idx, end_idx - start_idx + 1)};

	update_idxs();

	if(is_done())
		done = true;

	return result;
}


bool systheme::utils::Tokenizer::idxs_npos() const
{
	return start_idx == std::string::npos || end_idx == std::string::npos;
}

void systheme::utils::Tokenizer::idxs_to_first_token()
{
	start_idx = word.find_first_not_of(delimiter, 0);
	end_idx = word.find_first_of(delimiter, start_idx + 1) - 1;
}
void systheme::utils::Tokenizer::update_idxs()
{
	start_idx = word.find_first_not_of(delimiter, end_idx+1);
	end_idx = word.find_first_of(delimiter, start_idx+1) - 1;
}


bool systheme::utils::Tokenizer::is_done() const
{
	return done || idxs_npos() || word.empty();
}


void systheme::utils::Tokenizer::add_all_tokens(std::vector<std::string> &vector)
{
	while(!done){
		std::string next {next_token()};
		if(!next.empty())
			vector.push_back(next);
	}
}

void systheme::utils::Tokenizer::set_word(std::string input)
{
	word = std::move(input);
	reset();
}

void systheme::utils::Tokenizer::set_delimiter(std::string delim)
{
	delimiter = std::move(delim);
}

void systheme::utils::Tokenizer::reset()
{
	done = false;
	idxs_to_first_token();
}








