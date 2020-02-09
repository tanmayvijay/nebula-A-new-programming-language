// token types
#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum token_type {
	
	// empty token
	EMPTY,
	
	// single length tokens
	TOKEN_,

	// comments
	COMMENT,

	// any name not a keyword
	IDENTIFIER,

	// numbers
	INTEGER_LITERAL,

	// floats and doubles
	DECIMAL,

	// enclosed in braces, can be anything "Hey", "1234", "Hey12Hello 12346"
	STRING_LITERAL,

	// boolean ones
	BOOLEAN

	
};


#endif

