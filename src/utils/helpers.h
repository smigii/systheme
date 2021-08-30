//
// Created by smigii on 2021-04-04.
//

#ifndef SYSTHEME_HELPERS_H
#define SYSTHEME_HELPERS_H

#include <filesystem>
#include <ctime>

// Returns a string in the format MONTH-DAY-HOUR-MIN-SEC
[[nodiscard]] inline std::string get_time_stamp(){
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

// trim from start (in place)
inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

#endif //SYSTHEME_HELPERS_H
