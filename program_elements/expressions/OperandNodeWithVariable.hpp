#ifndef OPERAND_NODE_WITH_VARIABLE_H
#define OPERAND_NODE_WITH_VARIABLE_H

#include <iostream>

#include "ExpressionAST.hpp"
#include "../symbol_table/Variable.hpp"

class OperandNodeWithVariable : public ExpressionAST{
	Variable* variable;
	
	public:
		//constructor
		OperandNodeWithVariable(Variable* variable) : ExpressionAST(_OPERAND_NODE_){
			this->variable = variable;
		}
		
		
		//methods
		ValueType determine_final_type();
		
		std::string evaluate();
		
		void _repr_();
		
};


//implemetations
ValueType OperandNodeWithVariable::determine_final_type(){
	return this->variable->get_data_type();
}

std::string OperandNodeWithVariable::evaluate(){
	return this->variable->get_value();
}

void OperandNodeWithVariable::_repr_(){
	std::cout << " [ ";
	std::cout << variable->get_symbol_name();
	std::cout << " ] ";
}


#endif

