#ifndef PROGRAM_ELEMENTS_H
#define PROGRAM_ELEMENTS_H


#include<vector>
#include<iostream>

#include "value_type.hpp"
#include "expression_ast/expression_ast.hpp"



class Element{
	public:

		virtual void run() = 0;
		virtual void _repr_() = 0;

};

/////////////////////////////////////////////////

class Block : public Element{
	std::vector<Element*>* sub_elements;
	std::vector<Symbol*> symbol_table;
	Block* super_block = NULL;
	
	public:
		Block(Block* super_block = NULL){
			this->super_block = super_block;
		}
		
		Block(std::vector<Element*>* sub_elements, Block* super_block = NULL){
			this->super_block = super_block;
			this->sub_elements = sub_elements;
		}
		
		std::vector<Element*>* get_elements(){
			return this->sub_elements;
		}
		
		Block* get_super_block(){
			return this->super_block;
		}
		
		bool add_symbol(Symbol* symbol){ // returns true is symbol is successfullt added to block
			for (Symbol* sym : symbol_table){
				if (sym->get_symbol_name() == symbol->get_symbol_name()) return false;
			}
			this->symbol_table.push_back(symbol);
			return true;
		}
		
		// implement run
		void run(){
			std::cout << "Inside block" << std::endl;
		}
		
		void _repr_(){
			std::cout << std::endl << "------- BLOCK START -------" << std::endl;
			for(Element* e: *sub_elements){
				e->_repr_();
			}
			std::cout << std::endl << "------- BLOCK END -------" << std::endl;

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
		
		// implement _repr_() or leave it
		
		// implement run -- or leave it abstract
		
};



//////////////////////////////////////////////////

// those statements in which only an expression is there. like shell expressions.
class ExpressionStatement : public Statement{
	ExpressionAST* expression_ast;
	
	public:
		ExpressionStatement(Block* super_block, ExpressionAST* expression_ast) : Statement(super_block){
			this->expression_ast = expression_ast;
		}
		
		virtual void run(){ // implement this
			std::cout << "Inside Expression Statement run" << std::endl;
		}
		
		void _repr_(){
			std::cout << " ::: ";
			expression_ast->_repr_();
			std::cout << " :::" << std::endl;
		}
		
};



class VariableDeclarationStatement : public Statement{
	ValueType type;
	std::string name;
	ExpressionStatement* expression_sub_statement = NULL;
	
	public:
		VariableDeclarationStatement(Block* super_block, ValueType type, std::string name, ExpressionStatement* expression_sub_statement) : Statement(super_block){
			this->type = type;
			this->name = name;
			this->expression_sub_statement = expression_sub_statement;
		}
		
		
		void run(){
			std::cout << "Inside var decln" << std::endl;
		}
		
		void _repr_(){
			std::cout << std::endl << "VDS ~ " << this->type << " : " << this->name;
			
			if (expression_sub_statement)
				expression_sub_statement->_repr_();
			
			std::cout << std::endl;
		}

};


class VariableAssignmentStatement : public Statement{
	std::string variable_name;
	ExpressionStatement* expression_sub_statement;
	
	public:
		VariableAssignmentStatement(Block* super_block, std::string variable_name, ExpressionStatement* expression_sub_statement) : Statement(super_block){
			this->variable_name = variable_name;
			this->expression_sub_statement = expression_sub_statement;
		}
		
		void run() {
			std::cout << "Inside var assi" << std::endl;
		}
		
		void _repr_(){
			std::cout << std::endl << "VAS ~ " << this->variable_name;
			expression_sub_statement->_repr_();
			
			std::cout  <<  std::endl;
		}
	
};


// display statement
class OutputStatement : public Statement{
	std::vector<ExpressionStatement*> expressions;
	
	public:
		OutputStatement(Block* super_block, std::vector<ExpressionStatement*> expressions) : Statement(super_block){
			this->expressions = expressions;
		}
		
		void run() {
			std::cout << "Inside display statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << std::endl << "display: ~ \n";
			
			for(ExpressionStatement* exp : expressions){
				exp->_repr_();
			}
			
		}
};


// scan statement
//class InputStatement : public Statement{
//	
//};

#endif
