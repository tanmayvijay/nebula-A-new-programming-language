#ifndef EXPRESSION_STATEMENT_H
#define EXPRESSION_STATEMENT_H

#include "Statement.hpp"

// those statements in which only an expression is there. like shell expressions.
class ExpressionStatement : public Statement{
	ExpressionAST* expression_ast;
	
	public:
		//constructor
		ExpressionStatement(Block* super_block, ExpressionAST* expression_ast) : Statement(super_block){
			this->expression_ast = expression_ast;
		}
		
		
		//methods
		void run();
		
		ExpressionAST* get_expression();
		
		void check_semantic();
		
		void _repr_();
		
};


//implementations
void ExpressionStatement::run(){
	std::cout << this->expression_ast->evaluate() << "\n";
}


ExpressionAST* ExpressionStatement::get_expression(){
	return this->expression_ast;
}


void ExpressionStatement::check_semantic(){
	ValueType v_type = this->expression_ast->determine_final_type(); // since determine_final_type is also a semantic analyzer for expression asts
}


void ExpressionStatement::_repr_(){
	std::cout << " ::: ";
	expression_ast->_repr_();
	std::cout << " :::" << std::endl;
}

#endif

