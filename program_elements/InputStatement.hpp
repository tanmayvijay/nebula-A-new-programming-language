#ifndef INPUT_STATEMENT_H
#define INPUT_STATEMENT_H

#include "Statement.hpp"
#include "symbol_table/Variable.hpp"
#include "expressions/OperandNodeWithConstant.hpp"

// scan statement
class InputStatement : public Statement{
	std::vector<Variable*> variables;
	
	public:
		InputStatement(Block* super_block, std::vector<Variable*> variables) : Statement(super_block){
			this->variables = variables;
		}
		
		void check_semantic();
		
		void run();
		
		void _repr_();
};


void InputStatement::check_semantic(){
	return;
}


void InputStatement::run(){
	for (int i=0; i<this->variables.size(); i++){
		Variable* var = variables.at(i);
		std::string input;
		getline(std::cin, input);
		
		if (var->get_data_type() == _STRING_){
			ExpressionAST* val_expr = new OperandNodeWithConstant(_STRING_, input);
			var->set_value(val_expr);
		}
		else if (var->get_data_type() == _INTEGER_){
			long data = std::stol(input);
			ExpressionAST* val_expr = new OperandNodeWithConstant(_INTEGER_, std::to_string(data));
			var->set_value(val_expr);
		}
		else if (var->get_data_type() == _DOUBLE_){
			double data = std::stod(input);
			ExpressionAST* val_expr = new OperandNodeWithConstant(_DOUBLE_, std::to_string(data));
			var->set_value(val_expr);
		}
		else if (var->get_data_type() == _BOOLEAN_){
			ExpressionAST* val_expr;
			double numeric_input = 1;
			try{
				numeric_input = std::stod(input);
			}
			catch(...){
				
			}
			if (input == "False" || input == "" || numeric_input == 0)
				val_expr = new OperandNodeWithConstant(_BOOLEAN_, "False");
			else
				val_expr = new OperandNodeWithConstant(_BOOLEAN_, "True");
				
			var->set_value(val_expr);
		}
		else{
			std::cerr << "Inconsistent Types Error: void type not supported.";
			throw std::exception();
		}
		
		
	}
}

void InputStatement::_repr_(){
	std::cout << "scan:\t";
	
	for(Symbol* sym : variables){
		std::cout << sym->get_data_type() << " : " << sym->get_symbol_name() << " \t";
	}
	std::cout << "\n";
}

#endif

