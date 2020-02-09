//token data
#ifndef TOKEN_DATA
#define TOKEN_DATA

#include<regex>

#include "token_type.hpp"

using namespace std;


class token_data{
	basic_regex<char> pattern;
	token_type type;
	
	public:
		token_data(basic_regex<char> pattern, token_type type){
			this->pattern = pattern;
			this->type = type;
		}
		
		basic_regex<char> get_pattern(){
			return pattern;
		}
		
		token_type get_type(){
			return type;
		}
};


#endif

