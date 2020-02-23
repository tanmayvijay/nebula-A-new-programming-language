// tokenizer package
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<vector>
#include<string>
#include<regex>
#include<exception>
#include<iostream>

#include "token_type.hpp"
#include "token_data.hpp"
#include "token.hpp"

#include "../utils/utils.hpp"


class TOKENIZER{
	std::vector<TOKEN_DATA> token_datas;
	std::string str;
	TOKEN last_token;
	bool push_back_;
	
	public:
		TOKENIZER(std::string str){
			this->str = str;
			
			token_datas.push_back( TOKEN_DATA( std::basic_regex<char>("^(\".*\")"), STRING_LITERAL_ ) );
			token_datas.push_back( TOKEN_DATA( std::basic_regex<char>("^([a-zA-Z_][a-zA-Z_0-9]*)"), IDENTIFIER_ ) );
			token_datas.push_back( TOKEN_DATA( std::basic_regex<char>("^((-)?[0-9]+)"), INTEGER_LITERAL_ ) );
			
			
			for(std::string s: {"=", "\\(", "\\)", "\\.", "\\,"})
				token_datas.push_back(TOKEN_DATA(std::basic_regex<char>("^(" + s + ")"), TOKEN_));
			
		}
		
		TOKEN next_token(){
			str = _trim_(str);
			
			if (push_back_){
				push_back_ = false;
				return last_token;
			}
			
			if(str == "")
				return last_token = TOKEN("", EMPTY_);
				
			for(TOKEN_DATA td: token_datas){
				std::smatch matched_value;
				if ( regex_search(str, matched_value, td.get_pattern() ) ){
					std::string s = _trim_( matched_value.str() );
					
					str = regex_replace(str, basic_regex<char>(s), "", std::regex_constants::format_first_only);
					
					if(td.get_type() == STRING_LITERAL_)
						return last_token = TOKEN(s.substr(1, s.length()-2), STRING_LITERAL_);
					else
						return last_token = TOKEN(s, td.get_type() );
				}
			}
			
			throw std::invalid_argument("\"" + str + "\" cannot be parsed.");
		}
		
		
		bool has_next_token(){
			return !(this->str.empty());
		}
		
		void push_back(){
			if (last_token.exists())
				this->push_back_ = true;
		}
}; 


#endif






