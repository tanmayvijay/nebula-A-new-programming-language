// tokenizer package
#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<vector>
#include<regex>
#include<exception>

#include "token_type.hpp"
#include "token_data.hpp"
#include "token.hpp"

#include "../utils/utils.hpp"

class tokenizer{
	vector<token_data> token_datas;
	string str;
	token last_token;
	bool push_back;
	
	public:
		Tokenizer(string str){
			this->str = str;
			
			token_datas.push_back( token_data( basic_regex<char>("[a-zA-Z_][a-zA-Z_0-9]*"), IDENTIFIER ) );
			token_datas.push_back( token_data( basic_regex<char>("(-)?[0-9]+"), INTEGER_LITERAL ) );
			token_datas.push_back( token_data( basic_regex<char>("\".*\""), STRING_LITERAL ) );
			
			for(string s: {"=", "\(", "\)", "\.", "\,"})
				token_datas.push_back(token_data(basic_regex<char>(s), TOKEN_));
			
		}
		
		token next_token() throw (std::exception){
			str = trim(str);
			
			if (push_back){
				push_back = false;
				return last_token;
			}
			
			if(str == "")
				return last_token = token("", EMPTY);
				
			for(token_data td: token_datas){
				std::smatch matched_value;
				if ( regex_match(str, matched_value, td.get_pattern()) ){
					string s = trim( matched_value.str() );
					str = regex_replace(str, basic_regex<char>(s), "", std::regex_constants::format_first_only);
					
					if(td.get_type() == STRING_LITERAL)
						return last_token = token(s.substr(1, s.length()-1), STRING_LITERAL);
					else
						return last_token = token(s, td.get_type() );
					
				}
			}
			
			throw std::invalid_argument("\"" + str + "\" cannot be parsed.");
			
		}
};


#endif






