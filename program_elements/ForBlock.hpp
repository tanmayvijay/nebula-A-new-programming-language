#ifndef FOR_BLOCK_H
#define FOR_BLOCK_H

#include "Block.hpp"
#include "VariableAssignmentStatement.hpp"
#include "expressions/OperandNodeWithConstant.hpp"
#include "expressions/OperandNodeWithVariable.hpp"
#include "expressions/OperatorNode.hpp"


class ForBlock : public Block{
	ExpressionAST* condition_expr;
	VariableAssignmentStatement* loop_var_update;
	Variable* loop_variable;
	
	public:
		ForBlock(Block* super_block, std::string loop_variable_name, int lower_limit, int upper_limit, int step_size=1) : Block(super_block){
			
			OperandNodeWithConstant* lower_limit_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(lower_limit));
			
			OperandNodeWithConstant* upper_limit_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(upper_limit));
			
			OperandNodeWithConstant* step_size_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(step_size));
			
			this->loop_variable = new Variable(_INTEGER_, loop_variable_name, lower_limit_expression);
			this->add_symbol(loop_variable);
			OperandNodeWithVariable* loop_var_node = new OperandNodeWithVariable(loop_variable);
			
			OperatorNode* plus_op = new OperatorNode("+", _BINARY_OP_);
			plus_op->set_left_node(loop_var_node);
			plus_op->set_right_node(step_size_expression);
			
			this->loop_var_update = new VariableAssignmentStatement(this, this->loop_variable, plus_op);
			
			
			if (lower_limit <= upper_limit){
				if (step_size < 0)
					throw std::invalid_argument("Step size must be positive\n");
				OperatorNode* lte_op = new OperatorNode("<=", _BINARY_OP_);
				lte_op->set_left_node(loop_var_node);
				lte_op->set_right_node(upper_limit_expression);
				
				this->condition_expr = lte_op;
			}
			else{
				if (step_size > 0)
					throw std::invalid_argument("Step size must be negetive\n");
				OperatorNode* gte_op = new OperatorNode(">=", _BINARY_OP_);
				gte_op->set_left_node(loop_var_node);
				gte_op->set_right_node(upper_limit_expression);
				this->condition_expr = gte_op;
			}
			
			
		}
		
		
		void check_semantic();
		
		void run();
		
		void _repr_();
};


void ForBlock::check_semantic(){
	for(Element* elem : this->get_elements()){
		elem->check_semantic();
	}
	
	for(Symbol* symb : this->get_symbol_table()){
		if (symb->get_symbol_type() == _FUNCTION_){
			symb->check_semantic_in_symbol();
		}
	}
	
}


void ForBlock::run() {
	while(this->condition_expr->evaluate() == "True"){
		for(Element* elem : this->get_elements()){
			elem->run();
		}
		
		this->loop_var_update->run();
	}
	
}


void ForBlock::_repr_(){
	std::cout << "\n------------ FOR BLOCK -----------------\n";
	
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
	
	std::cout << "\n------------ FOR BLOCK END -------------\n";
}

#endif

