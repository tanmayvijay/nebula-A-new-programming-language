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
		virtual void check_semantic_in_symbol() = 0;
};



class Variable : public Symbol{
	
	ExpressionAST* value_expression = NULL;
	
	std::string value;
	
	
	public:
		Variable(ValueType data_type, std::string id_name, ExpressionAST* value_expression) : Symbol(_VARIABLE_, data_type, id_name){
			this->value_expression = value_expression;
//			this->value = value_expression->evaluate();
		}

		
		ExpressionAST* get_symbol_value_expression(){
			return this->value_expression;
		}
		
		void set_value(ExpressionAST* expression){
			this->value_expression = expression;
			this->value = value_expression->evaluate();
		}
		
		std::string get_value(){
			return this->value;
		}
		
		void check_semantic_in_symbol(){
			return;
		}
	
};




//class Block;




#endif
