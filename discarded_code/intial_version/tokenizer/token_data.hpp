//token data
#ifndef TOKEN_DATA_H
#define TOKEN_DATA_H

#include<regex>

#include "token_type.hpp"

using namespace std;


class TOKEN_DATA{
	basic_regex<char> pattern;
	TOKEN_TYPE type;
	
	public:
		TOKEN_DATA(basic_regex<char> pattern, TOKEN_TYPE type){
			this->pattern = pattern;
			this->type = type;
		}
		
		basic_regex<char> get_pattern(){
			return pattern;
		}
		
		TOKEN_TYPE get_type(){
			return type;
		}
};


#endif

