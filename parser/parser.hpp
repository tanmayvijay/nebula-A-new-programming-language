#ifndef PARSER
#define PARSER

#include "../blocks.hpp"
#include "../tokenizer/tokenizer.hpp"

template <class T>
class parser{
	
	virtual bool should_parse(string line) = 0;
	
	virtual T parse(block* super_block, tokenizer tokenizer_) = 0;
	
};


#endif
