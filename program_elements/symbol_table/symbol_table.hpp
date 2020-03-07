#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<string>

#include "../value_type.hpp"
#include "../expression_ast/expression_ast.hpp"

class Symbol{
	ValueType type;
	std::string id_name;
	ExpressionAST* value_expression = NULL;
	
	
	public:
		Symbol(ValueType type, std::string id_name, ExpressionAST* value){
			this->type = type;
			this->id_name = id_name;
			this->value_expression = value;
		}
		
		std::string get_symbol_name(){
			return this->id_name;
		}
		
		ValueType get_value_type(){
			return this->type;
		}
		
		ExpressionAST* get_symbol_value(){
			return this->value_expression;
		}
		
		void set_value(ExpressionAST* expression){
			this->value_expression = expression;
		}
	
};


#endif
