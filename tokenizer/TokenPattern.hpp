#ifndef TOKEN_PATTERN_H
#define TOKEN_PATTERN_H

#include<regex>

#include "TokenType.hpp"

class TokenPattern{
	TokenType pattern_type;
	std::basic_regex<char> pattern;
	
	public:
		//constructor
		TokenPattern(TokenType pattern_type, std::string pattern_str){
			this-> pattern_type = pattern_type;
			this->pattern = std::basic_regex<char> (pattern_str);
		}
		
		//methods
		TokenType get_pattern_type();
		
		std::basic_regex<char> get_pattern();
	
};



TokenType TokenPattern::get_pattern_type(){
	return this->pattern_type;
}

std::basic_regex<char> TokenPattern::get_pattern(){
	return this->pattern;
}

#endif

