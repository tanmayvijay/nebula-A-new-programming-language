// token

#ifndef TOKEN_H
#define TOKEN_H


#include<string>

#include "token_type.hpp"


class TOKEN{
	std::string token;
	TOKEN_TYPE type;
	
	public:
		TOKEN(){
			this->token = "";
			this->type = TOKEN_;
		}

		TOKEN(std::string token, TOKEN_TYPE type){
			this->token = token;
			this->type = type;
		}
		
		bool exists(){
			return this->token != "";
		}
		
		std::string get_token(){
			return token;
		}
		
		TOKEN_TYPE get_token_type(){
			return type;
		}
};

#endif

