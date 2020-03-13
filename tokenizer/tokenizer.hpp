#ifndef TOKENIZER_H
#define TOKENIZER_H

#include<string>
#include<vector>
#include<regex>
#include<iostream> // remove this

#include "../utils/utils.hpp"
#include "../exceptions/nebula_exceptions.hpp"

enum TokenType {
	_COMMENT_LITERAL_,
	_INTEGER_LITERAL_,
	_DECIMAL_LITERAL_,
	_BOOLEAN_LITERAL_,
	_STRING_LITERAL_,
	_IDENTIFIER_OR_KEYWORD_LITERAL_,
	_ARITHMETIC_OPERATOR_LITERAL_,
	_RELATIONAL_OPERATOR_LITERAL_,
	_LOGICAL_OPERATOR_LITERAL_,
	_OPEN_BRACKET_LITERAL_,
	_CLOSE_BRACKET_LITERAL_,
	_OPEN_PARENTHESIS_LITERAL_,
	_CLOSE_PARENTHESIS_LITERAL_,
	_OTHER_TOKEN_LITERAL_
};


class Token{
	TokenType token_type;
	std::string token_data;
	
	int line_no;
	int position;
	
	public:
		Token(TokenType token_type, std::string token_data, int line_no, int position){
			this->token_type = token_type;
			this->token_data = token_data;
			this->line_no = line_no;
			this->position = position;
		}
		
		
		// Methods
		TokenType get_token_type(){
			return this->token_type;
		}
		
		std::string get_token_data(){
			return this->token_data;
		}
		
		int get_line_no(){
			return this->line_no;
		}
		
		int get_position(){
			return this->position;
		}
};


class TokenPattern{
	TokenType pattern_type;
	std::basic_regex<char> pattern;
	
	public:
		
		TokenPattern(TokenType pattern_type, std::string pattern_str){
			this-> pattern_type = pattern_type;
			this->pattern = std::basic_regex<char> (pattern_str);
		}
		
		
		TokenType get_pattern_type(){
			return this->pattern_type;
		}
		
		std::basic_regex<char> get_pattern(){
			return this->pattern;
		}
	
};


class Tokenizer{
	std::vector<TokenPattern> patterns;
	
	public:
		Tokenizer(){
			
			this->patterns.push_back(
				TokenPattern(_COMMENT_LITERAL_, "^(\\$.*)")
			);
			
			this->patterns.push_back(
				TokenPattern(_STRING_LITERAL_, "^(\"(.*\\n?)*\")")
			);
			
//			operators
			
			std::string arithmetic_operators[] = {"\\*\\*", "\\+", "-", "\\*", "/", "%"};
			
			for (std::string op: arithmetic_operators){
				this->patterns.push_back(
					TokenPattern(_ARITHMETIC_OPERATOR_LITERAL_, "^(" + op + ")")
				);
			}
			
			
			std::string relational_operators[] = {"==", "\\!=", ">=", "<=", ">", "<"};
			
			for (std::string op: relational_operators){
				this->patterns.push_back(
					TokenPattern(_RELATIONAL_OPERATOR_LITERAL_, "^(" + op + ")")
				);
			}
			
			
			std::string logical_operators[] = {"and", "or", "not"};
			
			for (std::string op: logical_operators){
				this->patterns.push_back(
					TokenPattern(_LOGICAL_OPERATOR_LITERAL_, "^(" + op + ")\\b")
				);
			}

//			operators end
			
			this->patterns.push_back(
				TokenPattern(_BOOLEAN_LITERAL_, "^((True)|(False))\\b")
			);
			
			this->patterns.push_back(
				TokenPattern(_IDENTIFIER_OR_KEYWORD_LITERAL_, "^([a-zA-Z_][a-zA-Z0-9_]*)")
			);
			
			this->patterns.push_back(
				TokenPattern(_DECIMAL_LITERAL_, "^([0-9]+\\.[0-9]+)\\b")
			);
//			std::cout << "\nhere\n";
			this->patterns.push_back(
//				TokenPattern(_NUMBER_LITERAL_, "^([0-9]+(\\.[0-9]+)?)[^a-zA-Z_]")  // this one will cause probem when a number is at the end of line
				TokenPattern(_INTEGER_LITERAL_, "^([0-9]+)\\b")
			);
			
			this->patterns.push_back(
				TokenPattern(_OPEN_BRACKET_LITERAL_, "^(\\()")
			);
			
			this->patterns.push_back(
				TokenPattern(_CLOSE_BRACKET_LITERAL_, "^(\\))")
			);
			
			this->patterns.push_back(
				TokenPattern(_OPEN_PARENTHESIS_LITERAL_, "^(\\{)")
			);
			
			this->patterns.push_back(
				TokenPattern(_CLOSE_PARENTHESIS_LITERAL_, "^(\\})")
			);
			
			
			std::string other_tokens[] = {"=", "\\.", ","}; // "." token has no need yet
			
			for (std::string ot : other_tokens){
				this->patterns.push_back(
					TokenPattern(_OTHER_TOKEN_LITERAL_, "^(" + ot + ")")
				);
			}
			

			
		}
		
		// Methods
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
				
				for(TokenPattern pattern: this->patterns){
					std::smatch matched_value;
					
					if(std::regex_search(line, matched_value, pattern.get_pattern())){
						temp_token_data = matched_value[1].str();
						temp_token_type = pattern.get_pattern_type();
						
//						std::string temp_line;
//						std::regex_replace(std::back_inserter(temp_line), line.begin(), line.end(), std::basic_regex<char>(temp_token_data), "", std::regex_constants::format_first_only);
//						line = temp_line;

						line = line.substr(temp_token_data.length());
						
						pos += temp_token_data.length();
						matched_flag = true;
						break;
					}
				}
				
				if (!matched_flag){
					int error_position = pos - temp_token_data.length() + 1;
					throw InvalidCharacterError(original_line, line_no, error_position);	
				}
				
				if (temp_token_type != _COMMENT_LITERAL_){
					Token new_token = Token(temp_token_type, temp_token_data, line_no, pos);
			
					tokens_vector.push_back(new_token);
				}
				
			}

			
			return tokens_vector;
		}
};


#endif
