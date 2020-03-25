#ifndef CONDITIONAL_BLOCK_H
#define CONDITIONAL_BLOCK_H

#include "Block.hpp"
#include "expressions/OperandNodeWithConstant.hpp"
#include "expressions/OperatorNode.hpp"

class ConditionalBlock : public Block{ // for if, else if, else
										// else block has condition == NULL
										// super_block is an IFBlock
	ExpressionAST* condition_expression;
	public:
		ConditionalBlock(Block* super_block, ExpressionAST* condition_expression) : Block(super_block){
			if (condition_expression){
				OperandNodeWithConstant* or_False = new OperandNodeWithConstant(_BOOLEAN_);
				OperatorNode* or_node = new OperatorNode("or", _BINARY_OP_);
				or_node->set_left_node(condition_expression);
				or_node->set_right_node(or_False);
				condition_expression = or_node;
			}
			
			this->condition_expression = condition_expression;
		}
		
		
		ExpressionAST* get_condition_expression();
		
		void check_semantic();
		
		
		void run();
		
		void _repr_();
};



ExpressionAST* ConditionalBlock::get_condition_expression(){
	return this->condition_expression;
}

void ConditionalBlock::check_semantic(){
	if (condition_expression){
		ValueType condition_type = condition_expression->determine_final_type();
		if (condition_type == _STRING_){
			std::cerr << "Inconsistent Types Error: " << condition_type << " is not boolean.";
			throw std::exception();
		}
	}

	for(Element* elem : this->get_elements()){
		elem->check_semantic();
	}
	
	for(Symbol* symb : this->get_symbol_table()){
		if (symb->get_symbol_type() == _FUNCTION_){
//					((Function*)symb)->get_function_block()->check_semantic();
			symb->check_semantic_in_symbol();
		}
	}
	
//			std::cout << "condition block check pass\n";
}


void ConditionalBlock::run() {
	for(Element* elem : this->get_elements()){
		elem->run();
	}
}

void ConditionalBlock::_repr_(){
	std::cout << "------------ IF CONDITION -----------------\n";
	
	if (this->condition_expression){
		std::cout << "Condition: ";
		this->condition_expression->_repr_();
	}
	
	
	std::cout << "\nSymbol Table:\n";
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
	
	std::cout << "------------ IF CONDITION END -------------\n";
}

#endif

