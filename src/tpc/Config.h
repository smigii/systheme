//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_CONFIG_H
#define SYSTHEME_CONFIG_H

#include <string>
#include <vector>
#include <ostream>

class Config {
private:
	std::string name;
	std::string dest;
	std::vector<std::string> v_comps;

public:
	Config(std::string _name, std::string _dest);

	friend std::ostream& operator<<(std::ostream& os, const Config &conf);

	std::string get_name() const;
	std::string get_dest() const;

	std::string get_comp(int i) const;
	void add_comp(const std::string& comp);
};


#endif //SYSTHEME_CONFIG_H
