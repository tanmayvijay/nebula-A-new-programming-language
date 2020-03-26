#ifndef OPERAND_NODE_WITH_FUNCTION_CALL_H
#define OPERAND_NODE_WITH_FUNCTION_CALL_H

#include "ExpressionAST.hpp"
#include "../symbol_table/Function.hpp"

class OperandNodeWithFunctionCall : public ExpressionAST{
	Function* function_to_call;
	std::vector<ExpressionAST*> param_expressions;
	
	public:
		//constructor
		OperandNodeWithFunctionCall(Symbol* func_to_call, std::vector<ExpressionAST*> param_expressions) : ExpressionAST(_OPERAND_NODE_){
			this->function_to_call = (Function*) func_to_call;
			this->param_expressions = param_expressions;
		}
		
		
		//methods
		ValueType determine_final_type();
		
		std::string evaluate();
		
		void _repr_();
};


ValueType OperandNodeWithFunctionCall::determine_final_type(){ // check_semantic()
	if(param_expressions.size() != function_to_call->get_parameters().size())
		throw std::exception();
		
	for(int i=0; i< param_expressions.size(); i++){
		ValueType param_expr_type = param_expressions.at(i)->determine_final_type();
		ValueType param_type = function_to_call->get_parameters().at(i)->get_data_type();
		
		if (param_type == _DOUBLE_ && (param_expr_type == _DOUBLE_ || param_expr_type == _INTEGER_) )
			continue;
		

		if (param_expr_type != param_type){
			std::cerr << "Inconsistent Types Error: " << param_expr_type << " is not " << param_type << ".";
			throw std::exception();
		}
			
	}
	
	return this->function_to_call->get_return_type();
	
}


std::string OperandNodeWithFunctionCall::evaluate(){
//	this->function_to_call->execute(param_expressions);
//	return this->function_to_call->get_return_variable()->get_value();
	
	return this->function_to_call->execute(param_expressions);

}


void OperandNodeWithFunctionCall::_repr_(){
	std::cout << " [ Function Call: " << this->function_to_call->get_symbol_name() << " : ( ";
	for(ExpressionAST* exp : param_expressions){
		exp->_repr_();
		std::cout << ", ";
	}
	
	std::cout << ") ] = ";

	std::cout << this->function_to_call->get_return_variable()->get_value();
	
}

#endif
