#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<string>
#include<vector>

#include "../value_type.hpp"


//#include "../expression_ast/expression_ast.hpp"
class ExpressionAST;

enum SymbolType{
	_VARIABLE_,
	_FUNCTION_
};


class Symbol{
	SymbolType symbol_type;
	
	ValueType data_type;
	std::string id_name;
	
	public:
		Symbol(SymbolType s_type, ValueType data_type, std::string id_name){
			this->symbol_type = s_type;
			this->data_type = data_type;
			this->id_name = id_name;
		}
		
		SymbolType get_symbol_type(){
			return this->symbol_type;
		}
		
		std::string get_symbol_name(){
			return this->id_name;
		}
		
		ValueType get_data_type(){
			return this->data_type;
		}
		
		virtual ExpressionAST* get_symbol_value_expression() = 0;
};



class Variable : public Symbol{
	
	ExpressionAST* value_expression = NULL;
	
	
	public:
		Variable(ValueType data_type, std::string id_name, ExpressionAST* value) : Symbol(_VARIABLE_, data_type, id_name){
			this->value_expression = value;
		}

		
		ExpressionAST* get_symbol_value_expression(){
			return this->value_expression;
		}
		
		void set_value(ExpressionAST* expression){
			this->value_expression = expression;
		}
	
};




class Block;

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
		
		Symbol* get_return_variable(){
			return this->return_variable;
		}
		
		Block* get_function_block(){
			return this->function_block;
		}
		
		ExpressionAST* get_symbol_value_expression(){
			return this->return_variable->get_symbol_value_expression();
		}
		
};


#endif
