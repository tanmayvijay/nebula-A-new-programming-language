#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<string>

#include "../value_type.hpp"
#include "../program_elements.hpp"

class Symbol{
	ValueType type;
	std::string id_name;
	std::string value;
	Block* super_block;
	
	public:
		Symbol(ValueType type, std::string id_name, std::string value, Block* super_block){
			this->type = type;
			this->id_name = id_name;
			this->value = value;
			this->super_block = super_block;
		}
		
		std::string get_symbol_name(){
			return this->id_name;
		}
		
		ValueType get_value_type(){
			return this->type;
		}
		
		std::string get_symbol_value(){
			return this->value;
		}
	
};


#endif
