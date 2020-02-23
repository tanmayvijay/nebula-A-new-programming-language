#ifndef FUNCTION_BLOCK_H
#define FUNCTION_BLOCK_H

#include<string>
#include<vector>
#include<exception>

#include "block.hpp"
#include "../var_type.hpp"
#include "../parameter.hpp"
#include "../value.hpp"


class FUNCTION_BLOCK : public BLOCK{
	std::string name;
	VAR_TYPE return_type;
	std::vector<PARAMETER> params;
	VALUE* return_value = NULL;
	
	public:
		FUNCTION_BLOCK(BLOCK* super_block, std::string name, VAR_TYPE return_type, std::vector<PARAMETER> params) : BLOCK(super_block){
			this->name = name;
			this->return_type = return_type;
			this->params = params;
//			this->return_value = new VALUE(return_type, "");
		}
		
		
		void run(std::vector<VALUE> values){
//			std::string x = "run";
			invoke(values);
		}
		
		VALUE invoke(std::vector<VALUE> values){
			if (values.size() != params.size() )
				throw std::invalid_argument("Incorrect number of arguements.");
			
			for(int i=0; i<values.size(); i++){
				if (values.at(i).get_type() != params.at(i).get_type()){
					throw std::exception("Incorrect arguement type");
				}
				
				VARIABLE v = VARIABLE(values.at(i).get_type(), params.at(i).get_name(), values.at(i).get_value());
				add_variable(v);
			}
			
			for(BLOCK* b : get_sub_blocks()){
				b->run();
				
				if (return_value != NULL) break;
			}
			
			if (return_value == NULL && return_type != VOID_)
				throw std::exception("NULL returned, expected something else");
			
			
			VALUE local_return_value = *return_value;
			return_value = NULL;
			return local_return_value;
		}
};


#endif
