#ifndef PROGRAM_TOKENIZER_H
#define PROGRAM_TOKENIZER_H

#include<vector>
#include<string>
#include<queue>

#include "tokenizer/tokenizer.hpp"

queue<std::vector<Token> > tokenizing_helper(std::ifstream input_file){
	queue<std::vector<Token> > program_tokens;
	std::string line;

	Tokenizer tokenizer;
	
	while(std::getline(input_file, line)){
		std::vector<Token> line_tokens = tokenizer.tokenize(line);
		program_tokens.push(line_tokens);
	}
	
	return program_tokens;
}




#endif
