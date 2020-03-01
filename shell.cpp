#include<iostream>
#include<exception>
#include<fstream>
#include<string>
#include<vector>
#include<queue>

#include "tokenizing_helper.hpp"
#include "parsing_helper.hpp"
#include "program_elements/program_elements.hpp"
#include "tokenizer/tokenizer.hpp"

int main(int argc, char* argv[]){
	if (argc < 1) throw std::exception(); // change this
	std::string file_name = argv[1];
	
	std::ifstream input_file(file_name);
	
	queue<std::vector<Token> > program_tokens = tokenizing_helper(input_file);
	Block program_block = parsing_helper(program_tokens);
	
	return 0;
}
