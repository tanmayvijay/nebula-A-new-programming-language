// token types
#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TOKEN_TYPE {
	
	// empty token
	EMPTY_,
	
	// single length tokens
	TOKEN_,

	// comments
	COMMENT_,

	// any name not a keyword
	IDENTIFIER_,

	// numbers
	INTEGER_LITERAL_,

	// floats and doubles
	DECIMAL_LITERAL_,

	// enclosed in braces, can be anything "Hey", "1234", "Hey12Hello 12346"
	STRING_LITERAL_,

	// boolean ones
	BOOLEAN_LITERAL_

	
};


#endif

