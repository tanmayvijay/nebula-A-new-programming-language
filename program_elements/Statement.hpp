#ifndef STATEMENT_H
#define STATEMENT_H

#include "Element.hpp"
#include "Block.hpp"


class Statement : public Element{
	Block* super_block;
	public:
		//constructor
		Statement(Block* super_block){
			this->super_block = super_block;
		}
		
		Block* get_super_block();
		
};


//implementation
Block* Statement::get_super_block(){
	return this->super_block;
}

#endif

