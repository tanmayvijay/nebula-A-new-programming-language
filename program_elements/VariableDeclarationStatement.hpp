#ifndef VARIABLE_DECLARATION_STATEMENT_H
#define VARIABLE_DECLARATION_STATEMENT_H

#include "Statement.hpp"
#include "symbol_table/Variable.hpp"

class VariableDeclarationStatement : public Statement{
	ValueType type;
	Variable* var;
	ExpressionAST* value_expression = NULL;
	
	public:
		//constructor
		VariableDeclarationStatement(Block* super_block, ValueType type, Variable* var, ExpressionAST* value_expression) : Statement(super_block){
			this->type = type;
			this->var = var;
			this->value_expression = value_expression;
		}
		
		
		//methods
		void check_semantic();
		
		void run();
		
		void _repr_();

};


//implementations
void VariableDeclarationStatement::check_semantic(){
	ValueType expression_type = value_expression->determine_final_type();
//			std::cout << "vds semantic checking\n";
	if (expression_type == this->type) return;
	if (this->type == _DOUBLE_ && expression_type == _INTEGER_) return;
	if(this->type == _INTEGER_ && expression_type == _DOUBLE_) return;
	if(this->type == _BOOLEAN_ && (expression_type == _INTEGER_ || expression_type == _DOUBLE_) )
		return;
	
	std::cerr << "Inconsistent Types Error: " << expression_type << "is not supported.";
	throw std::exception();
}


void VariableDeclarationStatement::run(){
	this->var->set_value(this->value_expression);
}


void VariableDeclarationStatement::_repr_(){
	std::cout << "VDS ~ " << this->type << " :: " << this->var->get_symbol_name();
	
	if (value_expression){
		std::cout << " :: ";
		value_expression->_repr_();
	}
	
	std::cout << std::endl;
}

#endif

