#ifndef VARIABLE_ASSIGNMENT_STATEMENT_H
#define VARIABLE_ASSIGNMENT_STATEMENT_H

#include "Statement.hpp"
#include "symbol_table/Variable.hpp"

class VariableAssignmentStatement : public Statement{
	Variable* variable;
	ExpressionAST* expression;
	
	public:
		//constructor
		VariableAssignmentStatement(Block* super_block, Variable* variable, ExpressionAST* expression) : Statement(super_block){
			this->expression = expression;
			this->variable = variable;
			
		}
		
		void check_semantic();
		
		void run();
		
		void _repr_();
	
};


//implementations
void VariableAssignmentStatement::check_semantic(){
	if (this->variable->get_symbol_type() != _VARIABLE_){
		throw std::exception();
	}
	
	
	ValueType var_type = this->variable->get_data_type();
	ValueType expression_type = expression->determine_final_type();
	
	if (expression_type == var_type) return;
	if (var_type == _DOUBLE_ && expression_type == _INTEGER_) return;
	if(var_type == _INTEGER_ && expression_type == _DOUBLE_) return;
	if(var_type == _BOOLEAN_ && (expression_type == _INTEGER_ || expression_type == _DOUBLE_) )
		return;
		
	std::cerr << "Inconsistent Types Error: " << expression_type << "cannot be assigned to variable of type "<< var_type << ".";
	throw std::exception();
}


void VariableAssignmentStatement::run() {
	this->variable->set_value(this->expression);
}


void VariableAssignmentStatement::_repr_(){
	std::cout << "VAS ~ " << this->variable->get_symbol_name() << " :: ";
	expression->_repr_();
	
	std::cout << std::endl;
}

#endif

