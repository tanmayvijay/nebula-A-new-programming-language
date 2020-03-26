#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>

#include "Symbol.hpp"
#include "Variable.hpp"
#include "../Block.hpp"

class Function : public Symbol{
	std::vector<Variable*> parameters;
	Variable* return_variable;
	Block* function_block;
	
	public:
		//constructor
		Function(std::string func_name, std::vector<Variable*> parameters, ValueType return_type, Variable* return_variable, Block* function_block) : Symbol(_FUNCTION_, return_type, func_name){
			this->parameters = parameters;
			this->return_variable = return_variable;
			this->function_block = function_block;
		}
		
		
		//methods
		std::vector<Variable*> get_parameters();
		
		ValueType get_return_type();
		
		Variable* get_return_variable();
		
		Block* get_function_block();
		
		ExpressionAST* get_symbol_value_expression();
		
		std::string execute(std::vector<ExpressionAST*> param_expressions);
		
		void set_parameters(std::vector<ExpressionAST*> param_expressions);
		
		void check_semantic_in_symbol();
};


std::vector<Variable*> Function::get_parameters(){
	return this->parameters;
}


ValueType Function::get_return_type(){
	return this->get_data_type();
}


Variable* Function::get_return_variable(){
	return this->return_variable;
}


Block* Function::get_function_block(){
	return this->function_block;
}


ExpressionAST* Function::get_symbol_value_expression(){
	return this->return_variable->get_symbol_value_expression();
}


std::string Function::execute(std::vector<ExpressionAST*> param_expressions){
//	this->set_parameters(param_expressions);
//	this->function_block->run();
	std::vector<std::string> old_values;
	std::vector<std::string> new_values;
	for (int i=0; i<this->parameters.size(); i++){
		old_values.push_back(this->parameters.at(i)->get_value());
		
		std::string param_value = param_expressions.at(i)->evaluate();
		new_values.push_back(param_value);
	}
	
	for(int i=0; i<this->parameters.size(); i++){
		this->parameters.at(i)->set_value( new_values.at(i) );
	}
	
	this->function_block->run();
	std::string return_value = this->return_variable->get_value();
	
	for(int i=0; i<this->parameters.size(); i++){
		this->parameters.at(i)->set_value( old_values.at(i) );
	}
	
	return return_value;
}


//void Function::set_parameters(std::vector<ExpressionAST*> param_expressions){
//	for(int i=0; i<this->parameters.size(); i++){
//		Variable* param = this->parameters.at(i);
//		ExpressionAST* param_expr = param_expressions.at(i);
//		param->set_value(param_expr);
//	}
//}


void Function::check_semantic_in_symbol(){
	this->function_block->check_semantic();
}





#endif
