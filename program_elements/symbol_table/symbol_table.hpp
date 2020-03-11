#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<string>
#include<vector>

#include "../value_type.hpp"


//#include "../expression_ast/expression_ast.hpp"
class ExpressionAST;

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
		
		virtual ExpressionAST* get_symbol_value(){
			return this->value_expression;
		}
		
		void set_value(ExpressionAST* expression){
			this->value_expression = expression;
		}
	
};




class Block;

class Function : public Symbol{
	std::vector<Symbol*> parameters;
	Symbol* return_variable;
	Block* function_block;
	
	public:
		Function(std::string func_name, std::vector<Symbol*> parameters, ValueType return_type, Symbol* return_variable, Block* function_block) : Symbol(return_type, func_name, NULL){
			this->parameters = parameters;
			this->return_variable = return_variable;
			this->function_block = function_block;
		}
		
		std::string get_function_name(){
			return this->get_symbol_name();
		}
		
		std::vector<Symbol*> get_parameters(){
			return this->parameters;
		}
		
		ValueType get_return_type(){
			return this->get_value_type();
		}
		
		Symbol* get_return_variable(){
			return this->return_variable;
		}
		
		Block* get_function_block(){
			return this->function_block;
		}
		
		ExpressionAST* get_symbol_value(){ // returns return variable value expression
			return this->return_variable->get_symbol_value();
		}
		
};


#endif
