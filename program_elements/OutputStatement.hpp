#ifndef OUTPUT_STATEMENT_H
#define OUTPUT_STATEMENT_H


#include "Statement.hpp"

// display statement
class OutputStatement : public Statement{
	std::vector<ExpressionAST*> expressions;
	
	public:
		//constructor
		OutputStatement(Block* super_block, std::vector<ExpressionAST*> expressions) : Statement(super_block){
			this->expressions = expressions;
		}
		
		
		//methods
		void check_semantic();
		
		void run();
		
		void _repr_();
};


//implementations
void OutputStatement::check_semantic(){
	for(ExpressionAST* exp : this->expressions){
		exp->determine_final_type();
	}
}


void OutputStatement::run(){
	for (ExpressionAST* expr : this->expressions){
		std::cout << expr->evaluate() << " ";
	}
	std::cout << "\n";
}

void OutputStatement::_repr_(){
	std::cout << "display: ";
	
	for(ExpressionAST* exp : expressions){
		exp->_repr_();
		std::cout << " \t ";
	}
	
	std::cout << std::endl;
}

#endif

