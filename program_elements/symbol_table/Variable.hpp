#ifndef VARIABLE_H
#define VARIABLE_H


#include "Symbol.hpp"
#include "../expressions/ExpressionAST.hpp"

class Variable : public Symbol{
	ExpressionAST* value_expression = NULL;
	std::string value;
	
	public:
		//constructor
		Variable(ValueType data_type, std::string id_name, ExpressionAST* value_expression) : Symbol(_VARIABLE_, data_type, id_name){
			this->value_expression = value_expression;
			this->value = value_expression->evaluate();
		}

		
		//methods
		ExpressionAST* get_symbol_value_expression();
		
		void set_value(ExpressionAST* expression);
		
		std::string get_value();
		
		void check_semantic_in_symbol();
	
};


ExpressionAST* Variable::get_symbol_value_expression(){
	return this->value_expression;
}

void Variable::set_value(ExpressionAST* expression){
	this->value_expression = expression;
	this->value = value_expression->evaluate();
}

std::string Variable::get_value(){
	return this->value;
}

void Variable::check_semantic_in_symbol(){
	return;
}


#endif

