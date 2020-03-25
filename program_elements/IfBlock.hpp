#ifndef IF_BLOCK_H
#define IF_BLOCK_H

#include "Block.hpp"
#include "ConditionalBlock.hpp"


class IfBlock : public Block{ // sub-elements vector contains all the ConditionaBlocks.
	public:
		IfBlock(Block* super_block) : Block(super_block){
		}
		
		void check_semantic();
		
		void run();
		
		void _repr_();
};


void IfBlock::check_semantic(){
	for(Element* elem : this->get_elements()){
		elem->check_semantic();
	}
	
	for(Symbol* symb : this->get_symbol_table()){
		if (symb->get_symbol_type() == _FUNCTION_){
			symb->check_semantic_in_symbol();
		}
	}
	
}


void IfBlock::run() {
	std::vector<Element*> conditional_blocks = this->get_elements();
	for(int i=0; i<conditional_blocks.size(); i++){
		ConditionalBlock* cond_block = (ConditionalBlock*) conditional_blocks.at(i);
		
		if (cond_block->get_condition_expression()){
			std::string cond_state = cond_block->get_condition_expression()->evaluate();
			if (cond_state == "True"){
				cond_block->run();
				break;
			}
		}
		else{
			cond_block->run();
			break;
		}
		
	}
}

void IfBlock::_repr_(){
	std::cout << "\n------------ IF BLOCK -----------------\n";

	for(Element* e: this->get_elements()){
		e->_repr_();
	}
	
	std::cout << "\n------------ IF BLOCK END -------------\n";
}

#endif

