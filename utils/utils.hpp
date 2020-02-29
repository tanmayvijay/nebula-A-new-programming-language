#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<vector>
#include<regex>

// trim leading and trailing spaces from a string
std::string _trim_(const std::string& str, const std::string char_to_trim=" \t\n"){
	const auto str_begin = str.find_first_not_of(char_to_trim);
	if(str_begin == std::string::npos)
		return "";
		
	const auto str_end = str.find_last_not_of(char_to_trim);
	const auto str_range = str_end - str_begin + 1;
	
	return str.substr(str_begin, str_range);
}


std::string _trim_from_begin_(const std::string& str, const std::string char_to_trim=" \t\n"){
	const auto str_begin = str.find_first_not_of(char_to_trim);
	if(str_begin == std::string::npos)
		return "";
	
	return str.substr(str_begin);
}



std::string _trim_from_end_(const std::string& str, const std::string char_to_trim=" \t\n"){

	int str_begin = 0;
	const auto str_end = str.find_last_not_of(char_to_trim);
	const auto str_range = str_end - str_begin + 1;
	
	return str.substr(str_begin, str_range);
}



// split a string based on a delimiter
std::vector<std::string> _rex_split_(const std::string &s, std::string rgx_str = "\\s+"){
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



std::string _remove_extra_whitespace_ (const std::string input, std::string char_to_remove = "\\s+"){
	std::basic_regex<char> rex (char_to_remove);
	
	std::string output;
	std::regex_replace(std::back_inserter(output) ,input.begin(), input.end(), rex, " ");
	return output;
}

#endif
