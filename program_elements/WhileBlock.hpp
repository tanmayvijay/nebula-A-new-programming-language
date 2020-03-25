#ifndef WHILE_BLOCK_H
#define WHILE_BLOCK_H

#include "Block.hpp"

class WhileBlock : public Block{
	ExpressionAST* condition_expression;
	
	public:
		WhileBlock(Block* super_block, ExpressionAST* condition_expression) : Block(super_block){
			this->condition_expression = condition_expression;
		}
	
	
		void check_semantic();
		
		void run();
		
		void _repr_();
};


void WhileBlock::check_semantic(){
	ValueType condition_type = condition_expression->determine_final_type();
	if (condition_type == _STRING_){
		std::cerr << "Inconsistent Error Types: " << condition_type << "is not boolean.";
	}
	
	for(Element* elem : this->get_elements()){
		elem->check_semantic();
	}
	
	for(Symbol* symb : this->get_symbol_table()){
		if (symb->get_symbol_type() == _FUNCTION_){
			symb->check_semantic_in_symbol();
		}
	}
	
}

void WhileBlock::run() {
	while(this->condition_expression->evaluate() == "True"){
		for(Element* elem : this->get_elements()){
			elem->run();
		}
	}
}

void WhileBlock::_repr_(){
	std::cout << "\n------------ WHILE BLOCK -----------------\n";
	
	if (this->condition_expression){
		std::cout << "Condition: ";
		this->condition_expression->_repr_();
	}
	
	std::cout << "\n\nSymbol Table:\n";
	printf("%5s |%15s |%30s\n", "Type", "Name", "Value Expression");
	std::cout << "-------------------------------------------------------\n";
	for(Symbol* sym: this->get_symbol_table() ){
		printf("%5d |%15s | ", sym->get_data_type(), sym->get_symbol_name().c_str());
		sym->get_symbol_value_expression()->_repr_();
		std::cout << "\n";
	}

	std::cout << "\n\n";

	for(Element* e: this->get_elements()){
		e->_repr_();
	}
	
	std::cout << "\n------------ WHILE BLOCK END -------------\n";
}

#endif

