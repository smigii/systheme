//
// Created by smigii on 2021-04-04.
//

#ifndef SYSTHEME_HELPERS_HPP
#define SYSTHEME_HELPERS_HPP

#include <filesystem>
#include <ctime>

// Returns a string in the format MONTH-DAY-HOUR-MIN-SEC
[[nodiscard]] std::string get_time_stamp(){
	std::time_t time = std::time(0);
	std::tm* now = std::localtime(&time);

	std::string time_stamp =
		std::to_string(now->tm_mon + 1) + "-" +
		std::to_string(now->tm_mday) + "-" +
		std::to_string(now->tm_hour) + "-" +
		std::to_string(now->tm_min) + "-" +
		std::to_string(now->tm_sec);

	return time_stamp;
}

#endif //SYSTHEME_HELPERS_HPP
