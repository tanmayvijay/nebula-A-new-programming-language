#ifndef CLASS_H
#define CLASS_H

#include<string>

#include "block.hpp"

class CLASS_BLOCK : public BLOCK{
	
	std::string name;
	
	public:
		CLASS_BLOCK(std::string name) : BLOCK(NULL){
			
			this->name = name;
		}
		
		
		std::string get_name(){
			return this->name;
		}
		
		void run(){
			std::string x = "run";
		}
};



#endif
