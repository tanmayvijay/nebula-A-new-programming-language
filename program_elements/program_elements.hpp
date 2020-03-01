#ifndef PROGRAM_ELEMENTS_H
#define PROGRAM_ELEMENTS_H


#include<vector>

#include "variable/variable.hpp"
#include "expression/expression.hpp"



//enum element_types{
//	_ELEMENT_,
//	_STATEMENT_,
//	_BLOCK_,
//	_SIMPLE_STATEMENT_,
//	_COMPOUND_STATEMENT_	
//};


class Element{
	public:		
		virtual void run() = 0;
};

/////////////////////////////////////////////////

class Block : public Element{
	std::vector<Element*> sub_elements;
	std::vector<Variable> variables;
	Block* super_block;
	
	public:
		Block(Block* super_block = NULL){
			this->super_block = super_block;
		}
		
		
};


class Statement : public Element{
	Block* super_block;
	public:
		Statement(Block* super_block){
			this->super_block = super_block;
		}
		
};



//////////////////////////////////////////////////

// those statements in which only an expression is there. like shell expressions.
class SimpleStatement : public Statement{
	Expression* value_expression;
	
	public:
		SimpleStatement(Block* super_block, Expression* value_expression) : Statement(super_block){
			this->value_expression = value_expression;
		}
		
		virtual void run(){ // implement this
			
		}
		
};


//// for loops, while loops, if statements
//class CompoundStatement : public Statement{ // or this can just be merged with Block
//	vector<Statment*> sub_elements;
//	vector<Variable> variables;
//	
//	public:
//		CompoundStatement() // complete this
//		
//		
//		void run() // complete this
//		
//};

class FunctionCallStatement : public Statement{
	std::vector<Variable> parameters;
	
	public:
		FunctionCallStatement(){
			
		}
};


class VariableDeclarationStatement : public Statement{
	VariableType type;
	std::string name;
	Expression* value_expression;
	
	public:
		VariableDeclarationStatement() // complete this
		
		
		void run() override // implemtnt this

};


class VariableAssignmentStatement : public Statement{
	Variable* variable;
	Expression* value_expression;
	
	public:
		VariableAssignmentStatement() // complete this
		
		void run() // complete this
	
};



#endif
