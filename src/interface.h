//
// Created by smigii on 2021-08-29.
//

#ifndef SYSTHEME_INTERFACE_H
#define SYSTHEME_INTERFACE_H

#include <string>

// Main Systheme interface.
namespace systheme::interface {

	void apply_program_theme(const std::string& program, const std::string& theme);

	void apply_system_theme(const std::string& theme);

}


#endif //SYSTHEME_INTERFACE_H
