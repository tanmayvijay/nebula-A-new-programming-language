#ifndef OPERAND_NODE_WITH_CONSTANT_H
#define OPERAND_NODE_WITH_CONSTANT_H

#include<iostream>

#include "ExpressionAST.hpp"
#include "../../helpers/mappings.hpp"


class OperandNodeWithConstant : public ExpressionAST{
	ValueType operand_type;
	std::string operand_value;

	public:
		//constructor
		OperandNodeWithConstant(ValueType operand_type, std::string operand_value) : ExpressionAST(_OPERAND_NODE_){
			this->operand_type = operand_type;
			this->operand_value = operand_value;
		}
		
		//constructor
		OperandNodeWithConstant(ValueType operand_type) : ExpressionAST(_OPERAND_NODE_){
			this->operand_type = operand_type;
			this->operand_value = ValueType_to_default_value_mapping.find(operand_type)->second;
		}
		
		
		//methods
		ValueType determine_final_type();
		
		std::string evaluate();
		
		void _repr_();
};


ValueType OperandNodeWithConstant::determine_final_type(){
	return this->operand_type;
}

std::string OperandNodeWithConstant::evaluate(){
	return this->operand_value;
}

void OperandNodeWithConstant::_repr_(){
	std::cout << operand_value;
}

#endif

