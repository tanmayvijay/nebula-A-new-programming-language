#ifndef UTILS
#define UTILS

#include<string>
#include<vector>
#include<regex>


// trim leading and trailing spaces from a string
std::string trim(const std::string& str, const std::string char_to_trim=" \t\n\s"){
	const auto str_begin = str.find_first_not_of(char_to_trim);
	if(str_begin == std::string::npos)
		return "";
		
	const auto str_end = str.find_last_not_of(char_to_trim);
	const auto str_range = str_end - str_begin + 1;
	
	return str.substr(str_begin, str_range);
}


// slit string based on a delimiter
std::vector<std::string> rex_split(const std::string &s, const std::string& rgx_str = "\\s+"){
	std::vector<std::string> elems;
	std::basic_regex<char> rgx (rgx_str);
	
	std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
	std::sregex_token_iterator end;
	
	while(iter != end){
		if ((*iter).length() > 0)
			elems.push_back(*iter);
		++iter;
	}
	
	return elems;
}


#endif
