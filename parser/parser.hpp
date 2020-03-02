#ifndef PARSER_H
#define PARSER_H

#include<regex>
#include<string>
#include<vector>
#include<exception>
#include<queue>
#include<iostream>

#include "../program_elements/program_elements.hpp"
#include "../tokenizer/tokenizer.hpp"
#include "../utils/utils.hpp"


// declarations

class Parser{
	std::basic_regex<char> pattern;
	
	public:
		
		Parser(std::string pattern){
			this->pattern = std::basic_regex<char>(pattern);
		}
		
		std::basic_regex<char> get_pattern(){
			return this->pattern;
		}

		bool parsable(std::vector<Token> line_tokens){
			std::string line = "";
			for(Token& lt: line_tokens){
				line = line + lt.get_token_data() + " ";
			}
//			std::cout << line << std::endl;
			line = _trim_from_end_(line);
			return std::regex_match(line, pattern);
		}
		
		virtual Element* parse(std::queue<std::vector<Token> >& program_tokens) = 0;
};


// lowest priority
class SimpleStatementParser : public Parser{

	public:
		SimpleStatementParser() : Parser("^([a-zA-Z0-9_()+-*/%^ ]+)$"){}
		
		Element* parse(std::queue<std::vector<Token> >& program_tokens){
			// ****************************************** //
		}
};

class VariableDeclarationStatementParser : public Parser{
	
	public:
		VariableDeclarationStatementParser() : Parser("^([a-zA-Z_][a-zA-Z_0-9]* [a-zA-Z_][a-zA-Z_0-9]*( = .*)?)$"){}
		
		Element* parse(std::queue<std::vector<Token> >& program_tokens){
			
		}
		
};

class VariableAssignmentStatementParser : public Parser{
	
	public:
		VariableAssignmentStatementParser() : Parser("^([a-zA-Z_][a-zA-Z_0-9]* = .*)$"){}
		
		Element* parse(std::queue<std::vector<Token> >& program_tokens){
			
		}
};


////////////////////////////////////////////////////////////////////////////////
std::vector<Parser*> all_parsers;


std::vector<Element*> program_parser(std::queue<std::vector<Token> > program_tokens){
	
	all_parsers.push_back( new VariableDeclarationStatementParser() );
	all_parsers.push_back( new VariableAssignmentStatementParser() );
	all_parsers.push_back( new SimpleStatementParser() );
	
	
	std::vector<Element*> program_elements;
	
	while( !program_tokens.empty() ){
		std::vector<Token> line_tokens = program_tokens.front();
		program_tokens.pop();
		Element* next_element = NULL;
		
		bool line_parsed = false;
		for(Parser* parser : all_parsers){
			if (parser->parsable(line_tokens)){
//				next_element = parser->parse(program_tokens); //parser->parse() returns Element*
				line_parsed = true;
				break;
			}
		}
		
		if (!line_parsed){
//			std::cout << "here\n";
			throw std::exception();
		}
		
		program_elements.push_back(next_element);
		
	}
	
	return program_elements;
}



#endif
