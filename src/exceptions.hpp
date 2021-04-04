//
// Created by smigii on 2021-04-03.
//

#ifndef SYSTHEME_EXCEPTIONS_HPP
#define SYSTHEME_EXCEPTIONS_HPP

#include <string>
#include <stdexcept>

// === Exceptions ========================================================

class InvalidThemeException : public std::exception {
private:
	std::string path;

public:
	explicit InvalidThemeException(std::string path)
		: path{std::move(path)} {

	}

	[[nodiscard]] std::string msg () const noexcept{
		return "Theme does not exist, " + path;
	}
};

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

#endif //SYSTHEME_EXCEPTIONS_HPP
