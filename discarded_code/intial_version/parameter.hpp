#ifndef PARAMETER_H
#define PARAMETER_H

#include<string>

#include "var_type.hpp"

class PARAMETER{
	
	VAR_TYPE type_;
	std::string name;
	
	
	public:
		
		PARAMETER(VAR_TYPE type_, std::string name){
			this->type_ = type_;
			this->name = name;
		}
		
		VAR_TYPE get_type(){
			return this->type_;
		}
		
		std::string get_name(){
			return this->name;
		}
};

#endif
