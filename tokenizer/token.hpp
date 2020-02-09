// token

#ifndef TOKEN
#define TOKEN


#include<string>

#include "token_type.hpp"

using namespace std;


class token{
	string token_;
	token_type type;
	
	public:
		token(){
			this->token_ = "";
			this->type = TOKEN_;
		}

		token(string token_, token_type type){
			this->token_ = token_;
			this->type = type;
		}
		
		bool exists(){
			return this->token_ != "";
		}
		
		string get_token(){
			return token_;
		}
		
		token_type get_token_type(){
			return type;
		}
		
		
	
};

#endif

