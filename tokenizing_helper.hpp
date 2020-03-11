#ifndef PROGRAM_TOKENIZER_H
#define PROGRAM_TOKENIZER_H

#include<vector>
#include<string>
#include<queue>
#include<fstream>

#include "tokenizer/tokenizer.hpp"
#include "utils/utils.hpp"

std::queue<std::vector<Token> > tokenizing_helper(std::ifstream& input_file){
	std::queue<std::vector<Token> > program_tokens;
	std::string line;

	Tokenizer tokenizer;
	
	while(std::getline(input_file, line)){
		if (_trim_(line).length()){ // to handle empty tokens
			std::vector<Token> line_tokens = tokenizer.tokenize(line);
			if (line_tokens.size() > 0)
				program_tokens.push(line_tokens);
		}
	}
	
	return program_tokens;
}




#endif
