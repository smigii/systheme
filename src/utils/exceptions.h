//
// Created by smigii on 2021-04-03.
//

#ifndef SYSTHEME_EXCEPTIONS_H
#define SYSTHEME_EXCEPTIONS_H

#include <string>
#include <stdexcept>

// === Exceptions ========================================================

class NoConfigDirException : public std::exception {
private:
	std::string path;

public:
	explicit NoConfigDirException(std::string path)
		: path{std::move(path)} {

	}

	[[nodiscard]] std::string msg () const noexcept{
		return "No config directory exists, checked " + path;
	}
};


class SysthemeException : public std::exception {
private:
	std::string message;

public:
	explicit SysthemeException(std::string message)
	: message{std::move(message)} {}

	[[nodiscard]] std::string msg () const noexcept { return message; }
};

#endif //SYSTHEME_EXCEPTIONS_H
