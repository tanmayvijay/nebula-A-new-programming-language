#ifndef OPERAND_NODE_WITH_FUNCTION_CALL_H
#define OPERAND_NODE_WITH_FUNCTION_CALL_H

#include "expression_ast.hpp"
#include "../symbol_table/function.hpp"

class OperandNodeWithFunctionCall : public ExpressionAST{
	Function* function_to_call;
	std::vector<ExpressionAST*> param_expressions;
	
	public:
		OperandNodeWithFunctionCall(Symbol* func_to_call, std::vector<ExpressionAST*> param_expressions) : ExpressionAST(_OPERAND_NODE_){
			this->function_to_call = (Function*) func_to_call;
			this->param_expressions = param_expressions;
		}
		
		ValueType determine_final_type(){ // check_semantic()
//			std::cout << "in func determine type\n";
			if(param_expressions.size() != function_to_call->get_parameters().size())
				throw std::exception();
				
			for(int i=0; i< param_expressions.size(); i++){
				ValueType param_expr_type = param_expressions.at(i)->determine_final_type();
				ValueType param_type = function_to_call->get_parameters().at(i)->get_data_type();
				
				if (param_type == _DOUBLE_ && (param_expr_type == _DOUBLE_ || param_expr_type == _INTEGER_) )
					continue;
				
//				std::cout << "here!\n";
				if (param_expr_type != param_type)
					throw InconsistentTypesError();
			}
			
			return this->function_to_call->get_return_type();
			
		}
		
		std::string evaluate(){
			this->function_to_call->execute(param_expressions);
			return this->function_to_call->get_return_variable()->get_value();
		}
		
		void _repr_(){
			std::cout << " [ Function Call: " << this->function_to_call->get_symbol_name() << " : ( ";
			for(ExpressionAST* exp : param_expressions){
				exp->_repr_();
				std::cout << ", ";
			}
			
			std::cout << ") ] = ";

			std::cout << this->function_to_call->get_return_variable()->get_value();
			
		}
};

#endif
