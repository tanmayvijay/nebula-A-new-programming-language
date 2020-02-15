#ifndef FUNCTION_BLOCK_H
#define FUNCTION_BLOCK_H

#include<string>
#include<vector>

#include "block.hpp"
#include "../var_type.hpp"
#include "../parameter.hpp"
#include "../value.hpp"


class FUNCTION_BLOCK : public BLOCK{
	std::string name;
	VAR_TYPE return_type;
	std::vector<PARAMETER> params;
	VALUE return_value = VALUE(VAR_TYPE(0), "");
	
	public:
		FUNCTION_BLOCK(BLOCK* super_block, std::string name, VAR_TYPE return_type, std::vector<PARAMETER> params) : BLOCK(super_block){
			this->name = name;
			this->return_type = return_type;
			this->params = params;
			this->return_value = VALUE(return_type, "");
		}
		
		
		void run(){
			std::string x = "run";
		}
		
		void invoke(std::vector<VALUE> values){
			std::string x = "invooke";
		}
};


#endif
