//
// Created by smigii on 2021-04-03.
//

#ifndef SYSTHEME_EXCEPTIONS_H
#define SYSTHEME_EXCEPTIONS_H

#include <string>
#include <stdexcept>

class SysthemeException : public std::exception {
private:
	std::string message;

public:
	explicit SysthemeException(std::string message)
	: message{std::move(message)} {}

	[[nodiscard]] std::string msg () const noexcept { return message; }
};

#endif //SYSTHEME_EXCEPTIONS_H
