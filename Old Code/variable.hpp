#ifndef VARIABLE_H
#define VARIABLE_H

#include<string>

#include "value.hpp"
//#include "block/block.hpp"
#include "var_type.hpp"


class VARIABLE : public VALUE{
//	BLOCK* block;
	std::string name;
	
	public:
		VARIABLE(VAR_TYPE type, std::string name, std::string value) : VALUE(type, value){
//			this->block = block;
			this->name = name;
		}
		
			
//		BLOCK* get_block(){
//			return this->block;
//		}
		
		std::string get_name(){
			return this->name;
		}
};


#endif
