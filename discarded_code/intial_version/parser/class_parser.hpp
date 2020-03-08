#ifndef CLASS_PARSER_H
#define CLASS_PARSER_H

#include<regex>
#include<string>

#include "parser.hpp"
#include "../block/class_block.hpp"
#include "../utils/utils.hpp"
#include "../tokenizer/tokenizer.hpp"


class CLASS_PARSER : public PARSER<CLASS_BLOCK>{
	std::basic_regex<char> rex = std::basic_regex<char>("class [a-zA-Z_][a-zA-Z_]*{");
	public:
		bool parsable(std::string line){
			line = _trim_(line);
			return regex_match(line, rex);
		}
		
		CLASS_BLOCK parse(BLOCK* super_block, TOKENIZER tokenizer){
			tokenizer.next_token();
			
			std::string name = tokenizer.next_token().get_token();
			
			return CLASS_BLOCK(name);
		}
};

#endif
