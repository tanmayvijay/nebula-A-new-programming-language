#ifndef FUNCTION_H
#define FUNCTION_H

#include "symbol_table.hpp"
#include "../program_elements.hpp"

class Function : public Symbol{
	std::vector<Variable*> parameters;
	Variable* return_variable;
	Block* function_block;
	
	public:
		Function(std::string func_name, std::vector<Variable*> parameters, ValueType return_type, Variable* return_variable, Block* function_block) : Symbol(_FUNCTION_, return_type, func_name){
			this->parameters = parameters;
			this->return_variable = return_variable;
			this->function_block = function_block;
		}
		
		std::vector<Variable*> get_parameters(){
			return this->parameters;
		}
		
		ValueType get_return_type(){
			return this->get_data_type();
		}
		
		Variable* get_return_variable(){
			return this->return_variable;
		}
		
		Block* get_function_block(){
			return this->function_block;
		}
		
		ExpressionAST* get_symbol_value_expression(){
			return this->return_variable->get_symbol_value_expression();
		}
		
		void execute(std::vector<ExpressionAST*> param_expressions){
			this->set_parameters(param_expressions);
			this->function_block->run();
			
		}
		
		void set_parameters(std::vector<ExpressionAST*> param_expressions){
			for(int i=0; i<this->parameters.size(); i++){
				Variable* param = this->parameters.at(i);
				ExpressionAST* param_expr = param_expressions.at(i);
				param->set_value(param_expr);
			}
		}
		void check_semantic_in_symbol(){
			this->function_block->check_semantic();
		}
		
//		void clear_parameters(){
//			for(Variable* param : this->parameters){
//				ValueType type = param->get_data_type();
//				OperandNodeWithConstant default_expr = new OperandNodeWithConstant(type);
//				
//				param->set_value(default_expr);
//			}
//		}
		
};

#endif
