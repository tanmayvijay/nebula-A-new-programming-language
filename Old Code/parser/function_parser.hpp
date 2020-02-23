#ifndef FUNCTION_PARSER_H
#define FUNCTION_PARSER_H

#include<string>
#include<vector>
#include<map>
#include<bits/stdc++.h>


#include "parser.hpp"
#include "../block/function_block.hpp"
#include "../utils/utils.hpp"
#include "../tokenizer/tokenizer.hpp"
#include "../parameter.hpp"
#include "../var_type.hpp"


class FUNCTION_PARSER : public PARSER<FUNCTION_BLOCK>{
	std::basic_regex<char> rex = std::basic_regex<char>("fun [a-zA-Z_][a-zA-Z_0-9]* \\(([a-zA-Z_][a-zA-Z_0-9]* [a-zA-Z_][a-zA-Z_0-9]*)*\\) returns [a-zA-Z_][a-zA-Z_0-9]* [a-zA-Z_][a-zA-Z_0-9]*{");
	
	public:
		bool parsable(std::string line){
			line = _trim_(line);
			return regex_match(line, rex);
		}
		
		FUNCTION_BLOCK parse(BLOCK* super_block, TOKENIZER tokenizer){
			
			std::map<std::string, VAR_TYPE> var_type_mapping {
				{"STRING", STRING_},
				{"INTEGER", INTEGER_},
				{"BOOLEAN", BOOLEAN_},
				{"DECIMAL", DECIMAL_}
			};
				
			tokenizer.next_token();
			std::string name = tokenizer.next_token().get_token();
			tokenizer.next_token();
			
			TOKEN first_token = tokenizer.next_token();
			
			std::vector<PARAMETER> params;
			
			if (first_token.get_token() != ")"){

				while(tokenizer.has_next_token()){
					TOKEN token = tokenizer.next_token();
					if (token.get_token() == ")" || token.get_token() == "{") break;
					
					std::string type_ = token.get_token();
					std::transform(type_.begin(), type_.end(), type_.begin(), ::toupper);
					params.push_back(PARAMETER(var_type_mapping.find(type_)->second, tokenizer.next_token().get_token()));
				}
			}
			
			tokenizer.next_token();
			VAR_TYPE return_type = var_type_mapping.find(tokenizer.next_token().get_token())->second;
			
			return FUNCTION_BLOCK(super_block, name, return_type, params);
		}
};

#endif
