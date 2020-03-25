#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <iostream>

#include "TokenPattern.hpp"
#include "Token.hpp"
#include "../utils/utils.hpp"


//declarations
std::vector<Token> tokenize (std::string& line, int& line_no);


std::vector<TokenPattern> token_patterns = {
	TokenPattern(_COMMENT_LITERAL_, "^(\\$.*)"),
	
	TokenPattern(_STRING_LITERAL_, "^(\"(.*\\n?)*\")"),
	
	TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(\\*\\*)"),
	TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(\\+)"),
	TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(-)"),
	TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(\\*)"),
	TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(/)"),
	TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(%)"),
	
	TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(==)"),
	TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(\\!=)"),
	TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(>=)"),
	TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(<=)"),
	TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(>)"),
	TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(<)"),
	
	TokenPattern(_LOGICAL_OPERATOR_LITERAL_, "^(and)\\b"),
	TokenPattern(_LOGICAL_OPERATOR_LITERAL_, "^(or)\\b"),
	TokenPattern(_LOGICAL_OPERATOR_LITERAL_, "^(not)\\b"),
	
	TokenPattern(_BOOLEAN_LITERAL_, "^((True)|(False))\\b"),
	
	TokenPattern(_IDENTIFIER_OR_KEYWORD_LITERAL_, "^([a-zA-Z_][a-zA-Z0-9_]*)"),
	
	TokenPattern(_DOUBLE_LITERAL_, "^([0-9]+\\.[0-9]+)\\b"),
	
	TokenPattern(_INTEGER_LITERAL_, "^([0-9]+)\\b"),
	
	TokenPattern(_OPEN_BRACKET_LITERAL_, "^(\\()"),
	
	TokenPattern(_CLOSE_BRACKET_LITERAL_, "^(\\))"),
	
	TokenPattern(_OPEN_PARENTHESIS_LITERAL_, "^(\\{)"),
	
	TokenPattern(_CLOSE_PARENTHESIS_LITERAL_, "^(\\})"),
	
	TokenPattern(_OTHER_TOKEN_LITERAL_, "^(=)"),
	TokenPattern(_OTHER_TOKEN_LITERAL_, "^(\\.)"),
	TokenPattern(_OTHER_TOKEN_LITERAL_, "^(,)")
};
		
		
std::vector<Token> tokenize (std::string& line, int& line_no){
	// line is the original string with original whitespaces
	std::string original_line = line;
	
	std::vector<Token> tokens_vector;
	int pos = 0;
	line = _trim_from_end_(line);
	int line_length = line.length();
	
	while(pos < line_length){
		int str_begin = line.find_first_not_of(" \t");
		pos += str_begin;
		line = _trim_from_begin_(line);
		
		std::string temp_token_data;
		TokenType temp_token_type;
		bool matched_flag = false;
		
		for(TokenPattern pattern: token_patterns){
			std::smatch matched_value;
			
			if(std::regex_search(line, matched_value, pattern.get_pattern())){
				temp_token_data = matched_value[1].str();
				temp_token_type = pattern.get_pattern_type();

				line = line.substr(temp_token_data.length());
				
				matched_flag = true;
				break;
			}
		}
		
		if (!matched_flag){
			int error_position = pos + 1;
			std::cerr << "Invalid Character Error: " << line_no << " : " << error_position;
			throw std::exception();
		}

		pos += temp_token_data.length();

		
		if (temp_token_type == _STRING_LITERAL_)
			temp_token_data = temp_token_data.substr(1, temp_token_data.length()-2);
		
		if (temp_token_type != _COMMENT_LITERAL_){
			
			Token new_token = Token(temp_token_type, temp_token_data, line_no, pos);
			tokens_vector.push_back(new_token);
		}
		
		
	}

	
	return tokens_vector;
}


#endif
