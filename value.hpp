#ifndef VALUE_H
#define VALUE_H


#include<string>

#include "var_type.hpp"



class VALUE{
	
	VAR_TYPE type_;
	std::string value;
	
	public:
		
		VALUE(VAR_TYPE type_, std::string value){
			this->type_ = type_;
			this->value = value;
		}
		
		
		VAR_TYPE get_type(){
			return this->type_;
		}
		
		
		std::string get_value(){
			return this->value;
		}
		
		
		void set_value(std::string value){
			this->value = value;
		}
};




#endif
