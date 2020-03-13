#ifndef TOKEN_H
#define TOKEN_H



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



#endif
