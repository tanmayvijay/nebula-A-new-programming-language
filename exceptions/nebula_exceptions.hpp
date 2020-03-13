#ifndef NEBULA_EXCEPTIONS_H
#define NEBULA_EXCEPTIONS_H

#include<iostream>
#include<cstdlib>

#include<exception>
#include<string>


class InvalidCharacterError : public std::exception{
	int position;
	int line_no;
	std::string line_text;
	
	public:
		InvalidCharacterError(std::string line, int line_no, int position){
			this->position = position;
			this->line_no = line_no;
			this->line_text = line;
		}
		
		const char* what() const throw(){
			
			std::cerr << line_text << "\n";
			for(int i=1; i<position; i++)
				std::cerr << " ";
			std::cerr << "^\n";
			
			const char* error_message = ("at position: " + std::to_string(this->position) + " on line: " + std::to_string(this->line_no) + "\n").c_str();
			return error_message;
		}
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
	abort();
}

#endif

