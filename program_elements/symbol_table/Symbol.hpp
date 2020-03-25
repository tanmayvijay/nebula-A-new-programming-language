#ifndef SYMBOL_H
#define SYMBOL_H

#include<string>

#include "SymbolType.hpp"
#include "../ValueType.hpp"


class ExpressionAST; //forward declaration

class Symbol{
	SymbolType symbol_type;
	
	ValueType data_type;
	std::string id_name;
	
	public:
		//constructor
		Symbol(SymbolType s_type, ValueType data_type, std::string id_name){
			this->symbol_type = s_type;
			this->data_type = data_type;
			this->id_name = id_name;
		}
		
		//methods
		SymbolType get_symbol_type();
		
		std::string get_symbol_name();
		
		ValueType get_data_type();
		
		virtual ExpressionAST* get_symbol_value_expression() = 0;
		
		virtual void check_semantic_in_symbol() = 0;
};


SymbolType Symbol::get_symbol_type(){
	return this->symbol_type;
}

std::string Symbol::get_symbol_name(){
	return this->id_name;
}

ValueType Symbol::get_data_type(){
	return this->data_type;
}

#endif
