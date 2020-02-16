#ifndef BLOCKS_H
#define BLOCKS_H

#include<string>
#include<vector>

#include "../variable.hpp"

//class VARIABLE;
class BLOCK{
	BLOCK* super_block;
	std::vector<BLOCK*> sub_blocks;
	std::vector<VARIABLE*> variables;
	
	public:
		
		BLOCK(BLOCK* super_block){
			this->super_block = super_block;
		}
		
		void add_block(BLOCK* block_){
			this->sub_blocks.push_back(block_);
		}
		
		
		VARIABLE* get_variable(std::string name){
			for (int i=0; i<variables.size(); i++){
				if (variables.at(i)->get_name() == name) return variables.at(i);
			}
			return NULL;
		}
		
		
		BLOCK* get_super_block(){
			return this->super_block;
		}
		
		void add_variable(VARIABLE& variable){
			variables.push_back(&variable);
		}
		
		virtual void run() = 0;
};


#endif
