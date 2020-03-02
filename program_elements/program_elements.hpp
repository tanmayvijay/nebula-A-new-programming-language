#ifndef PROGRAM_ELEMENTS_H
#define PROGRAM_ELEMENTS_H


#include<vector>
#include<iostream>

#include "variable/variable.hpp"
#include "expression_ast/expression_ast.hpp"



class Element{
	public:

		virtual void run() = 0;
};

/////////////////////////////////////////////////

class Block : public Element{
	std::vector<Element*> sub_elements;
	std::vector<Variable*> variables; // added while executing program
	Block* super_block = NULL;
	
	public:
		Block(Block* super_block = NULL){
			this->super_block = super_block;
		}
		
		Block(std::vector<Element*> sub_elements, Block* super_block = NULL){
			this->super_block = super_block;
			this->sub_elements = sub_elements;
		}
		
		std::vector<Element*> get_elements(){
			return this->sub_elements;
		}
		
//		void add_element(Element* sub_element){
//			this->sub_elements.push_back(sub_element);
//		}
//		
//		void add_elements(std::vector<Element*> sub_elements){
//			this->sub_elements = sub_elements;
//		}
		
		void add_variable(Variable* variable){ // used while executing program
			this->variables.push_back(variable);
		}
		
		Block* get_super_block(){
			return this->super_block;
		}
		
		// implement run
		void run(){
			std::cout << "Inside block" << std::endl;
		}
		
		// implement find_variable
		
};


class Statement : public Element{
	Block* super_block;
	public:
		Statement(Block* super_block){
			this->super_block = super_block;
		}
		
		Block* get_super_block(){
			return this->super_block;
		}
		
		
		// implement run -- or leave it abstract
		
};



//////////////////////////////////////////////////

// those statements in which only an expression is there. like shell expressions.
class SimpleStatement : public Statement{
	ExpressionAST* expression_ast;
	
	public:
		SimpleStatement(Block* super_block, ExpressionAST* expression_ast) : Statement(super_block){
			this->expression_ast = expression_ast;
		}
		
		virtual void run(){ // implement this
			std::cout << "Inside Simple Statement run" << std::endl;
		}
		
};


//class FunctionCallStatement : public Statement{
//	std::vector<Variable> parameters;
//	
//	public:
//		FunctionCallStatement(){
//			
//		}
//};


class VariableDeclarationStatement : public Statement{
	VariableType type;
	std::string name;
	ExpressionAST* value_expression_ast;
	
	public:
		VariableDeclarationStatement(Block* super_block, VariableType type, std::string name, ExpressionAST value_Expression_ast) : Statement(super_block){
			this->type = type;
			this->name = name;
			this->value_expression_ast = value_expression_ast;
		}
		
		
		void run(){
			std::cout << "Inside var decln" << std::endl;
		}

};


class VariableAssignmentStatement : public Statement{
	Variable* variable;
	ExpressionAST* value_expression_ast;
	
	public:
		VariableAssignmentStatement(Block* super_block, Variable* variable, ExpressionAST* value_expression_ast) : Statement(super_block){
			this->variable = variable;
			this->value_expression_ast = value_expression_ast;
		}
		
		void run() {
			std::cout << "Inside var assi" << std::endl;
		}
	
};



#endif
