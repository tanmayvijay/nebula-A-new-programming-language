#include<iostream>

#include "tokenizing_helper.hpp"
#include "parser/parser.hpp"


int main(int argc, char* argv[]){
	
	if (argc < 2){
		std::cerr << "No file path provided.\n";
		throw std::exception();
	}
	
	std::string file_name = argv[1];
	
	
	std::ifstream input_file(file_name);
	
	std::queue<std::vector<Token> > program_tokens = tokenizing_helper(input_file);
	
	Block* program_block = program_parser(program_tokens);

	program_block->check_semantic();
	
	program_block->run();
	
//	parser tests - 2 
//	if(!program_block->get_elements()->at(0)) std::cout << "Empty block\n";
//	program_block->_repr_();
	
//	parser_tests
//	for(Element* e : program_block.get_elements()){
//		if (!e) std::cout << "NULL\n";
//	}
	
//	tokenizer tests
//	while(!program_tokens.empty()){
//		std::vector<Token> t = program_tokens.front();
//		program_tokens.pop();
//		
//		for(Token x: t){
//			std::cout << "'" << x.get_token_data() << "'" << std::endl;
//		}
//		std::cout << std::endl;
//	}


		
	return 0;
}
