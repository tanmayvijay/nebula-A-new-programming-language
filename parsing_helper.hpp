// retuns program block
#ifndef PARSING_HELPER_H
#define PARSING_HELPER_H

#include<vector>
#include<queue>

#include "program_elements/program_elements.hpp"
#include "tokenizer/tokenizer.hpp"
#include "parser/parser.hpp"

Block parsing_helper(std::queue<std::vector<Token> > program_tokens){
	
	std::vector<Element*> program_block_elements = program_parser(program_tokens);
	
	Block program_block(program_block_elements, NULL);
	
	return program_block;
}

#endif
