#ifndef NEBULA_EXCEPTIONS_H
#define NEBULA_EXCEPTIONS_H

#include<iostream>
#include<cstdlib>

#include<exception>
#include<string>
#include<vector>

#include "../tokenizer/token.hpp"


class NebulaException : public std::exception{
	int position;
	int line_no;
	std::string line_text;
	
	public:
		NebulaException(std::string line_text, int line_no, int position){
			this->position = position;
			this->line_no = line_no;
			this->line_text = line_text;
		}
		
		NebulaException(std::vector<Token>& line_tokens, int line_no, int position){
			this->line_no = line_no;
			this->position = position;
			
			std::string line_text = "";
			
			int pos = 0;
			for(Token& t: line_tokens){
				while(pos < t.get_position()){
					 line_text += " ";
					 pos++;
				}
				line_text += t.get_token_data();
				pos += t.get_token_data().length();
			}
			
			this->line_text = line_text;
		}
		
		int get_position() const{
			return this->position;
		}
		
		int get_line_no() const{
			return this->line_no;
		}
		
		std::string get_line_text() const{
			return this->line_text;
		}
};


class InvalidCharacterError : public NebulaException{
	
	
	public:
		InvalidCharacterError(std::string line_text, int line_no, int position) : NebulaException(line_text, line_no, position){
		}
		
		const char* what() const throw(){
			
			std::cerr << this->get_line_text() << "\n";
			for(int i=1; i<this->get_position(); i++)
				std::cerr << " ";
			std::cerr << "^\n";
			
			const char* error_message = ("at position: " + std::to_string(this->get_position()) + " on line: " + std::to_string(this->get_line_no()) + "\n").c_str();
			return error_message;
		}
};


class MissingExpressionError : public NebulaException{
	
	public:
		MissingExpressionError(std::vector<Token>& line_tokens, int line_no, int position) : NebulaException(line_tokens, line_no, position){
		}
		
		const char* what() const throw(){
			
			std::cerr << this->get_line_text() << "\n";
			for(int i=1; i<this->get_position(); i++)
				std::cerr << " ";
			std::cerr << "^\n";
			
			const char* error_message = ("at position: " + std::to_string(this->get_position()) + " on line: " + std::to_string(this->get_line_no()) + "\n").c_str();
			return error_message;
		}
};




class InvalidSyntaxError : public NebulaException{
	
	public:
		InvalidSyntaxError(std::vector<Token>& line_tokens, int line_no, int position) : NebulaException(line_tokens, line_no, position){
		}
		
		const char* what() const throw(){
			std::cerr << this->get_line_text() << "\n";
			for(int i=1; i<this->get_position(); i++)
				std::cerr << " ";
			std::cerr << "^\n";
			
			const char* error_message = ("at position: " + std::to_string(this->get_position()) + " on line: " + std::to_string(this->get_line_no()) + "\n").c_str();
			return error_message;
		}
};


class InconsistentTypesError : public std::exception{
		
};



void terminate_handler(){
	std::cerr << "Execution terminated!\n\n";
	std::exception_ptr cur_exp = std::current_exception();
	try{
		std::rethrow_exception(cur_exp);
	}
	catch(InvalidCharacterError &e){
		std::cerr << "InvalidCharacterError: " << e.what() << "\n";
	}
	catch(MissingExpressionError &e){
		std::cerr << "MissingExpressionError: " << e.what() << "\n";
	}
	catch(InvalidSyntaxError &e){
		std::cerr << "InvalidSyntaxError: " << e.what() << "\n";
	}
	catch(InconsistentTypesError &e){
		std::cerr << "InconsistentTypesError: " <<  "\n";
	}
	catch(...){
		std::cerr << "Error: " <<  "\n";
	}
	
	abort();
}

#endif

