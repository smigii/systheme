//
// Created by smigii on 2021-01-23.
//

#ifndef SYSTHEME_VEC_SORT_H
#define SYSTHEME_VEC_SORT_H

#include <vector>
#include <string>
#include <algorithm>

void vec_sort(const std::vector<std::string>& v_template, std::vector<std::string>& v_operand){
	int idx = 0;
	std::vector<std::string>::iterator it;

	for(const std::string& str : v_template){
		if(idx == v_operand.size()-1)
			break;

		it = std::find(v_operand.begin()+idx, v_operand.end(), str);
		if(it != v_operand.end()){
			int find_loc = it - v_operand.begin();
			std::swap(v_operand.at(idx), v_operand.at(find_loc));
			idx++;
		}
	}

}

#endif //SYSTHEME_VEC_SORT_H
