#ifndef BLOCKS
#define BLOCKS

#include<vector>


class block{
	block* super_block;
	std::vector<block*> sub_blocks;
	
	public:
		
		block(block* super_block){
			this->super_block = super_block;
		}
		
		void add_block(block* block_){
			this->sub_blocks.push_back(block_);
		}
		
		block* get_super_block(){
			return this->super_block;
		}
		
		virtual void run() = 0;
};


#endif
