#ifndef PARSER_H
#define PARSER_H

#include<regex>
#include<string>
#include<vector>
#include<exception>
#include<queue>

#include "../program_elements/program_elements.hpp"
#include "../tokenizer/tokenizer.hpp"
#include "../utils/utils.hpp"


// declarations
class Parser;
class SimpleStatementParser;
class VariableDeclarationStatementParser;
class VariableAssignmentStatementParser;

std::vector<Parser*> parsers;
parsers.push_back( &VariableDeclarationStatementParser() );
parsers.push_back( &VariableAssignmentStatementParser() );
parsers.push_back( &SimpleStatementParser() );


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
			line = _trim_from_end_(line);
			return std::regex_match(line, pattern);
		}
		
		virtual Element* parse(queue<std::vector<Token> >& program_tokens) = 0;
};


// lowest priority
class SimpleStatementParser : public Parser{

	public:
		SimpleStatementParser() : Parser("^([a-zA-Z0-9_()]+)$"){}
		
		Element* parse(queue<std::vector<Token> >& program_tokens){
			// ****************************************** //
		}
};

class VariableDeclarationStatementParser : Parser{
	
	public:
		VariableDeclarationStatementParser() : Parser("^([a-zA-Z_][a-zA-Z_0-9]+ [a-zA-Z_][a-zA-Z_0-9]+( = .*)?)$"){}
		
		Element* parse(queue<std::vector<Token> >& program_tokens){
			
		}
		
};

class VariableAssignmentStatementParser : Parser{
	
	public:
		VariableAssignmentStatementParser() : Parser("^([a-zA-Z_][a-zA-Z_0-9]+ = .*)$"){}
		
		Element* parse(queue<std::vector<Token> >& program_tokens){
			
		}
};


////////////////////////////////////////////////////////////////////////////////




queue<Element*> program_parser(queue<std::vector<Token> > program_tokens){
	
	queue<Element*> program_elements;
	
	while( !program_tokens.empty() ){
		std::vector<Token> line_tokens = queue.front();
		
		Element* next_element = NULL;
		
		bool line_parsed = false;
		for(Parser* parser : parsers){
			if parser->parsable(line_tokens){
				next_element = parser->parse(program_tokens); //parser->parse() returns Element*
				line_parsed = true;
				break;
			}
		}
		
		if (!line_parsed) throw std::exception();
		
		program_elements.push(next_element);
		
	}
	
	return program_elements;
}



#endif
