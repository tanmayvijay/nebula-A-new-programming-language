#ifndef PARSER_H
#define PARSER_H

#include<string>

#include "../block/block.hpp"
#include "../tokenizer/tokenizer.hpp"

template <class T>
class PARSER{
	
	virtual bool parsable(std::string line) = 0;
	
	virtual T parse(BLOCK* super_block, TOKENIZER tokenizer) = 0;
	
};


#endif
