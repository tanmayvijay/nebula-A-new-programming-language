#ifndef PROGRAM_ELEMENTS_H
#define PROGRAM_ELEMENTS_H


#include<vector>
#include<iostream>

#include "value_type.hpp"
#include "expression_ast/expression_ast.hpp"
#include "symbol_table/symbol_table.hpp"




class Element{
	public:

		virtual void run() = 0;
		virtual void _repr_() = 0;
};

/////////////////////////////////////////////////

class Block : public Element{
	std::vector<Element*> sub_elements;
	std::vector<Symbol*> symbol_table;
	Block* super_block = NULL;
	
	public:
		Block(Block* super_block = NULL){
			this->super_block = super_block;
		}

		// getters		
		std::vector<Element*> get_elements(){
			return this->sub_elements;
		}
		
		std::vector<Symbol*> get_symbol_table(){
			return this->symbol_table;
		}
		
		Block* get_super_block(){
			return this->super_block;
		}
		
		// setters
		void add_element(Element* element){
			this->sub_elements.push_back(element);
		}
		
		bool add_symbol(Symbol* symbol){ // returns true if symbol is successfully added to block
			for (Symbol* sym : symbol_table){
				if (sym->get_symbol_name() == symbol->get_symbol_name()){
					std::cout << "\nSymbol : '" << sym->get_symbol_name() << "' alreaady exists!\n";
					throw std::exception();
				}
			}
			this->symbol_table.push_back(symbol);
		}
		
		
		// other methods
		bool check_symbol_already_exists_in_this_block(std::string sym_name){
			for (Symbol* sym : symbol_table){
				if (sym->get_symbol_name() == sym_name){
					return true;
				}
			}
			
			return false;
		}
		
		Symbol* find_symbol(std::string sym_name){
			bool found_symbol = false;
			Symbol* symbol_to_return = NULL;
			for(Symbol* sym : symbol_table){
				if (sym->get_symbol_name() == sym_name){
					symbol_to_return = sym;
					found_symbol = true;
				}
			}
			
			if (!found_symbol){
				if (this->super_block)
				symbol_to_return = this->super_block->find_symbol(sym_name);
				
				if (!symbol_to_return){
					std::cout << "\nSymbol '" << sym_name << "' not found\n";
					throw std::exception();
				}
			}
			
			return symbol_to_return;
		}
		
		
		void run(){
			std::cout << "Inside block" << std::endl;
		}
		
		void _repr_(){
			std::cout << std::endl << "------- BLOCK START -------" << std::endl;
			std::cout << "\nSymbol Table:\n";
			printf("%5s |%15s |%30s\n", "Type", "Name", "Value Expression");
			std::cout << "-------------------------------------------------------\n";
			for(Symbol* sym: symbol_table){
				printf("%5d |%15s | ", sym->get_data_type(), sym->get_symbol_name().c_str());
				sym->get_symbol_value_expression()->_repr_();
				std::cout << "\n";
			}
		
			std::cout << "\n\n";
			for(Element* e: sub_elements){
				e->_repr_();
			}

			std::cout << std::endl << "------- BLOCK END -------" << std::endl;

		}
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
		
		ExpressionAST* get_expression(){
			return this->expression_ast;
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
	ExpressionAST* value_expression = NULL;
	
	public:
		VariableDeclarationStatement(Block* super_block, ValueType type, std::string name, ExpressionAST* value_expression) : Statement(super_block){
			this->type = type;
			this->name = name;
			this->value_expression = value_expression;
		}
		
		
		void run(){
			std::cout << "Inside var decln" << std::endl;
		}
		
		void _repr_(){
			std::cout << "VDS ~ " << this->type << " :: " << this->name;
			
			if (value_expression){
				std::cout << " :: ";
				value_expression->_repr_();
			}
			
			std::cout << std::endl;
		}

};


class VariableAssignmentStatement : public Statement{
	std::string variable_name;
	ExpressionAST* expression;
	
	public:
		VariableAssignmentStatement(Block* super_block, std::string variable_name, ExpressionAST* expression) : Statement(super_block){
			this->variable_name = variable_name;
			this->expression = expression;
		}
		
		void run() {
			std::cout << "Inside var assi" << std::endl;
		}
		
		void _repr_(){
			std::cout << "VAS ~ " << this->variable_name << " :: ";
			expression->_repr_();
			
			std::cout << std::endl;
		}
	
};


// display statement
class OutputStatement : public Statement{
	std::vector<ExpressionAST*> expressions;
	
	public:
		OutputStatement(Block* super_block, std::vector<ExpressionAST*> expressions) : Statement(super_block){
			this->expressions = expressions;
		}
		
		void run() {
			std::cout << "Inside display statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << "display: ";
			
			for(ExpressionAST* exp : expressions){
				exp->_repr_();
				std::cout << " \t ";
			}
			
			std::cout << std::endl;
		}
};


// scan statement
class InputStatement : public Statement{
	std::vector<Symbol*> variables;
	
	public:
		InputStatement(Block* super_block, std::vector<Symbol*> variables) : Statement(super_block){
			this->variables = variables;
		}
		
		
		void run() {
			std::cout << "Inside scan statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << "scan:\t";
			
			for(Symbol* sym : variables){
				std::cout << sym->get_data_type() << " : " << sym->get_symbol_name() << " \t";
			}
			std::cout << "\n";
		}
};



/////////////////////////// BLOCKS //////////////////////////////////

class ConditionalBlock : public Block{ // for if, else if, else
										// else block has condition == NULL
										// super_block is an IFBlock
	ExpressionAST* condition_expression;
	public:
		ConditionalBlock(Block* super_block, ExpressionAST* condition_expression) : Block(super_block){
			this->condition_expression = condition_expression;
		}
		
		void run() {
			std::cout << "Inside conditional statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << "------------ IF CONDITION -----------------\n";
			
			if (this->condition_expression){
				std::cout << "Condition: ";
				this->condition_expression->_repr_();
			}
			
			
			std::cout << "\nSymbol Table:\n";
			printf("%5s |%15s |%30s\n", "Type", "Name", "Value Expression");
			std::cout << "-------------------------------------------------------\n";
			for(Symbol* sym: this->get_symbol_table() ){
				printf("%5d |%15s | ", sym->get_data_type(), sym->get_symbol_name().c_str());
				sym->get_symbol_value_expression()->_repr_();
				std::cout << "\n";
			}
			
//			std::cout << "\n\nFunction - Function Table:\n";
//			printf("%5s |%15s |\n", "Ret. Type", "Func Name");
//			std::cout << "-------------------------------------------------------\n";
//			for(Function* func : this->get_function_table()){
//				printf("%5d |%15s |\n", func->get_return_type(), func->get_function_name().c_str());
//			}
		
			std::cout << "\n\n";
			
			for(Element* e: this->get_elements()){
				e->_repr_();
			}
			
			std::cout << "------------ IF CONDITION END -------------\n";
		}
		
		
};



class IfBlock : public Block{ // sub-elements vector contains all the ConditionaBlocks.
	public:
		IfBlock(Block* super_block) : Block(super_block){
		}
		
		void run() {
			std::cout << "Inside if statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << "\n------------ IF BLOCK -----------------\n";

			for(Element* e: this->get_elements()){
				e->_repr_();
			}
			
			std::cout << "\n------------ IF BLOCK END -------------\n";
		}
};


class ForBlock : public Block{
	int lower_limit;
	int higher_limit;
	int step_size;
	Symbol* loop_variable;
	public:
		ForBlock(Block* super_block, std::string loop_variable_name, int ll, int hl, int ss=1) : Block(super_block){
			this->lower_limit = ll;
			this->higher_limit = hl;
			this->step_size = ss;
			
			OperandNodeWithConstant* loop_variable_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(lower_limit));
			this->loop_variable = new Variable(_INTEGER_, loop_variable_name, loop_variable_expression);
			this->add_symbol(loop_variable);
		}
		
		
		void run() {
			std::cout << "Inside for statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << "\n------------ FOR BLOCK -----------------\n";
			
			std::cout << "\nSymbol Table:\n";
			printf("%5s |%15s |%30s\n", "Type", "Name", "Value Expression");
			std::cout << "-------------------------------------------------------\n";
			for(Symbol* sym: this->get_symbol_table() ){
				printf("%5d |%15s | ", sym->get_data_type(), sym->get_symbol_name().c_str());
				sym->get_symbol_value_expression()->_repr_();
				std::cout << "\n";
			}
			
//			std::cout << "\n\nFunction - Function Table:\n";
//			printf("%5s |%15s |\n", "Ret. Type", "Func Name");
//			std::cout << "-------------------------------------------------------\n";
//			for(FunctionBlock* func : this->get_function_table()){
//				printf("%5d |%15s |\n", func->get_return_type(), func->get_function_name().c_str());
//			}
		
			std::cout << "\n\n";

			for(Element* e: this->get_elements()){
				e->_repr_();
			}
			
			std::cout << "\n------------ FOR BLOCK END -------------\n";
		}
		
};



class WhileBlock : public Block{
	ExpressionAST* condition_expression;
	
	public:
		WhileBlock(Block* super_block, ExpressionAST* condition_expression) : Block(super_block){
			this->condition_expression = condition_expression;
		}
		
		void run() {
			std::cout << "Inside for statement" << std::endl;
		}
		
		void _repr_(){
			std::cout << "\n------------ WHILE BLOCK -----------------\n";
			
			if (this->condition_expression){
				std::cout << "Condition: ";
				this->condition_expression->_repr_();
			}
			
			std::cout << "\n\nSymbol Table:\n";
			printf("%5s |%15s |%30s\n", "Type", "Name", "Value Expression");
			std::cout << "-------------------------------------------------------\n";
			for(Symbol* sym: this->get_symbol_table() ){
				printf("%5d |%15s | ", sym->get_data_type(), sym->get_symbol_name().c_str());
				sym->get_symbol_value_expression()->_repr_();
				std::cout << "\n";
			}
			
//			std::cout << "\n\nFunction - Function Table:\n";
//			printf("%5s |%15s |\n", "Ret. Type", "Func Name");
//			std::cout << "-------------------------------------------------------\n";
//			for(Function* func : this->get_function_table()){
//				printf("%5d |%15s |\n", func->get_return_type(), func->get_function_name().c_str());
//			}
		
			std::cout << "\n\n";

			for(Element* e: this->get_elements()){
				e->_repr_();
			}
			
			std::cout << "\n------------ WHILE BLOCK END -------------\n";
		}
		
		
};






#endif
