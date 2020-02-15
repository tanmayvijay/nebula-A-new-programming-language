#ifndef VARIABLE_PARSE_H
#define VARIABLE_PARSE_H

#include<map>
#include<string>
#include<exception>

#include "parser.hpp"
#include "../utils/utils.hpp"
#include "../block/block.hpp"
#include "../tokenizer/tokenizer.hpp"
#include "../var_type.hpp"
#include "../tokenizer/token.hpp"
#include "../tokenizer/token_type.hpp"



class VARIABLE_PARSER : public PARSER<BLOCK*>{
	std::basic_regex<char> rex = std::basic_regex<char>("var [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]* = \"?.*\"?");
	public:
		bool parsable(std::string line){
			line = _trim_(line);
			return regex_match(line, rex);
		}
		
	
	BLOCK* parse(BLOCK* super_block, TOKENIZER tokenizer){
		tokenizer.next_token();
		
		
		std::map<std::string, VAR_TYPE> var_type_mapping {
			{"STRING", STRING_},
			{"INTEGER", INTEGER_},
			{"BOOLEAN", BOOLEAN_},
			{"DECIMAL", DECIMAL_}
		};
		
		std::string type_ = tokenizer.next_token().get_token();
		transform(type_.begin(), type_.end(), type_.begin(), ::toupper);
		VAR_TYPE type = var_type_mapping.find(type_)->second;
		
		std::string name = tokenizer.next_token().get_token();
		
		tokenizer.next_token();
		
		TOKEN value_token = tokenizer.next_token();
		
		std::string value;
		value = value_token.get_token();
		
		
		
		
	}
};

#endif
