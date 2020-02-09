#ifndef UTILS
#define UTILS

#include<iostream>
#include<string>

std::string trim(const std::string& str, const std::string char_to_trim=" \t"){
	const auto str_begin = str.find_first_not_of(char_to_trim);
	if(str_begin == std::string::npos)
		return "";
		
	const auto str_end = str.find_last_not_of(char_to_trim);
	const auto str_range = str_end - str_begin + 1;
	
	return str.substr(str_begin, str_range);
}

int main(){
	std::cout << trim("tst test		 test") << "-";
}


#endif
