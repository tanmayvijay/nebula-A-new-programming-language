#ifndef BLOCKS_H
#define BLOCKS_H

#include<vector>

//#include "../variable.hpp"

class VARIABLE;
class BLOCK{
	BLOCK* super_block;
	std::vector<BLOCK*> sub_blocks;
	std::vector<VARIABLE> variables;
	
	public:
		
		BLOCK(BLOCK* super_block){
			this->super_block = super_block;
		}
		
		void add_block(BLOCK* block_){
			this->sub_blocks.push_back(block_);
		}
		
		BLOCK* get_super_block(){
			return this->super_block;
		}
		
		virtual void run() = 0;
};


#endif
