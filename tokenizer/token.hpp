#ifndef TOKEN_H
#define TOKEN_H

#include<string>

#include "TokenType.hpp"


class Token{
	TokenType token_type;
	std::string token_data;
	
	int line_no;
	int position;
	
	public:
		//constructor
		Token(TokenType token_type, std::string token_data, int line_no, int position){
			this->token_type = token_type;
			this->token_data = token_data;
			this->line_no = line_no;
			this->position = position;
		}
		
		
		// Methods
		TokenType get_token_type();
		
		std::string get_token_data();
		
		int get_line_no();
		
		int get_position();
};

TokenType Token::get_token_type(){
	return this->token_type;
}

std::string Token::get_token_data(){
	return this->token_data;
}

int Token::get_line_no(){
	return this->line_no;
}

int Token::get_position(){
	return this->position;
}



#endif
