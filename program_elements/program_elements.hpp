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
		virtual void check_semantic() = 0;
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
		
		void check_semantic(){

			for(Element* elem : this->sub_elements){
				elem->check_semantic();
			}
			
			for(Symbol* symb : this->symbol_table){
				if (symb->get_symbol_type() == _FUNCTION_){
					
//					((Function*)symb)->get_function_block()->check_semantic();
					symb->check_semantic_in_symbol();
				}
			}
			
//			std::cout << "block check pass\n";
			
		}
		
		
		void run(){
//			std::cout << "Inside block" << std::endl;
			for(Element* elem : this->sub_elements) elem->run();
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
		
		void run(){ // implement this
			std::cout << this->expression_ast->evaluate() << "\n";
		}
		
		ExpressionAST* get_expression(){
			return this->expression_ast;
		}
		
		void check_semantic(){
			ValueType v_type = this->expression_ast->determine_final_type(); // since determine_final_type is also a semantic analyzer for expression asts
//			std::cout << "expression statement check pass\n";
		}
		
		void _repr_(){
			std::cout << " ::: ";
			expression_ast->_repr_();
			std::cout << " :::" << std::endl;
		}
		
};



class VariableDeclarationStatement : public Statement{
	ValueType type;
	Variable* var;
	ExpressionAST* value_expression = NULL;
	
	public:
		VariableDeclarationStatement(Block* super_block, ValueType type, Variable* var, ExpressionAST* value_expression) : Statement(super_block){
			this->type = type;
			this->var = var;
			this->value_expression = value_expression;
		}
		
		void check_semantic(){
			ValueType expression_type = value_expression->determine_final_type();
//			std::cout << "vds semantic checking\n";
			if (expression_type == this->type) return;
			if (this->type == _DOUBLE_ && expression_type == _INTEGER_) return;
			if(this->type == _INTEGER_ && expression_type == _DOUBLE_) return;
			if(this->type == _BOOLEAN_ && (expression_type == _INTEGER_ || expression_type == _DOUBLE_) )
				return;
				
			throw InconsistentTypesError();
		}
		
		void run(){
			this->var->set_value(this->value_expression);
		}
		
		void _repr_(){
			std::cout << "VDS ~ " << this->type << " :: " << this->var->get_symbol_name();
			
			if (value_expression){
				std::cout << " :: ";
				value_expression->_repr_();
			}
			
			std::cout << std::endl;
		}

};


class VariableAssignmentStatement : public Statement{
	Variable* variable;
	ExpressionAST* expression;
	
	public:
		VariableAssignmentStatement(Block* super_block, Variable* variable, ExpressionAST* expression) : Statement(super_block){
			this->expression = expression;
			this->variable = variable;
			
		}
		
		void check_semantic(){
			if (this->variable->get_symbol_type() != _VARIABLE_){
				throw std::exception();
			}
			
//			std::cout << "vas semantic checking\n";
			
			ValueType var_type = this->variable->get_data_type();
			ValueType expression_type = expression->determine_final_type();
			
//			std::cout << var_type << "\t" << expression_type
			
			if (expression_type == var_type) return;
			if (var_type == _DOUBLE_ && expression_type == _INTEGER_) return;
			if(var_type == _INTEGER_ && expression_type == _DOUBLE_) return;
			if(var_type == _BOOLEAN_ && (expression_type == _INTEGER_ || expression_type == _DOUBLE_) )
				return;
				
			throw InconsistentTypesError();
		}
		
		void run() {
			this->variable->set_value(this->expression);
		}
		
		void _repr_(){
			std::cout << "VAS ~ " << this->variable->get_symbol_name() << " :: ";
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
		
		void check_semantic(){
			for(ExpressionAST* exp : this->expressions){
				exp->determine_final_type();
			}
//			std::cout << "output statement check pass\n";
		}
		
		void run() {
			for (ExpressionAST* expr : this->expressions){
				std::cout << expr->evaluate() << " ";
			}
			std::cout << "\n";
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
	std::vector<Variable*> variables;
	
	public:
		InputStatement(Block* super_block, std::vector<Variable*> variables) : Statement(super_block){
			this->variables = variables;
		}
		
		void check_semantic(){
//			std::cout << "input stmt semantic checking\n";
			return;
		}
		
		
		void run() {
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
					throw InconsistentTypesError();
				}
				
				
			}
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
			if (condition_expression){
				OperandNodeWithConstant* or_False = new OperandNodeWithConstant(_BOOLEAN_);
				OperatorNode* or_node = new OperatorNode("or", _BINARY_OP_);
				or_node->set_left_node(condition_expression);
				or_node->set_right_node(or_False);
				condition_expression = or_node;
			}
			
			this->condition_expression = condition_expression;
		}
		
		ExpressionAST* get_condition_expression(){
			return this->condition_expression;
		}
		
		void check_semantic(){
			if (condition_expression){
				ValueType condition_type = condition_expression->determine_final_type();
				if (condition_type == _STRING_)
					throw InconsistentTypesError();
			}

			for(Element* elem : this->get_elements()){
				elem->check_semantic();
			}
			
			for(Symbol* symb : this->get_symbol_table()){
				if (symb->get_symbol_type() == _FUNCTION_){
//					((Function*)symb)->get_function_block()->check_semantic();
					symb->check_semantic_in_symbol();
				}
			}
			
//			std::cout << "condition block check pass\n";
		}
		
		
		void run() {
			for(Element* elem : this->get_elements()){
				elem->run();
			}
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
		
		void check_semantic(){
			for(Element* elem : this->get_elements()){
				elem->check_semantic();
			}
			
			for(Symbol* symb : this->get_symbol_table()){
				if (symb->get_symbol_type() == _FUNCTION_){
//					((Function*)symb)->get_function_block()->check_semantic();
					symb->check_semantic_in_symbol();
				}
			}
			
//			std::cout << "if block check pass\n";
		}
		
		void run() {
			std::vector<Element*> conditional_blocks = this->get_elements();
			for(int i=0; i<conditional_blocks.size(); i++){
				ConditionalBlock* cond_block = (ConditionalBlock*) conditional_blocks.at(i);
				
				if (cond_block->get_condition_expression()){
					std::string cond_state = cond_block->get_condition_expression()->evaluate();
					if (cond_state == "True"){
						cond_block->run();
						break;
					}
//					else{
//						continue;
//					}
				}
				else{
					cond_block->run();
					break;
				}
				
			}
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
//	int lower_limit;
//	int higher_limit;
//	int step_size;
	ExpressionAST* condition_expr;
	VariableAssignmentStatement* loop_var_update;
	Variable* loop_variable;
	public:
		ForBlock(Block* super_block, std::string loop_variable_name, int lower_limit, int upper_limit, int step_size=1) : Block(super_block){
//			this->lower_limit = ll;
//			this->higher_limit = hl;
//			this->step_size = ss;
			
			OperandNodeWithConstant* lower_limit_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(lower_limit));
			
			OperandNodeWithConstant* upper_limit_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(upper_limit));
			
			OperandNodeWithConstant* step_size_expression = new OperandNodeWithConstant(_INTEGER_, std::to_string(step_size));
			
			this->loop_variable = new Variable(_INTEGER_, loop_variable_name, lower_limit_expression);
			this->add_symbol(loop_variable);
			OperandNodeWithVariable* loop_var_node = new OperandNodeWithVariable(loop_variable);
			
			OperatorNode* plus_op = new OperatorNode("+", _BINARY_OP_);
			plus_op->set_left_node(loop_var_node);
			plus_op->set_right_node(step_size_expression);
			
			this->loop_var_update = new VariableAssignmentStatement(this, this->loop_variable, plus_op);
			
//			this->add_element(loop_var_update);
			
			
			if (lower_limit <= upper_limit){
				if (step_size < 0)
					throw std::invalid_argument("Step size must be positive\n");
				OperatorNode* lte_op = new OperatorNode("<=", _BINARY_OP_);
				lte_op->set_left_node(loop_var_node);
				lte_op->set_right_node(upper_limit_expression);
				
				this->condition_expr = lte_op;
			}
			else{
				if (step_size > 0)
					throw std::invalid_argument("Step size must be negetive\n");
				OperatorNode* gte_op = new OperatorNode(">=", _BINARY_OP_);
				gte_op->set_left_node(loop_var_node);
				gte_op->set_right_node(upper_limit_expression);
				this->condition_expr = gte_op;
			}
			
			
		}
		
		void check_semantic(){
			for(Element* elem : this->get_elements()){
				elem->check_semantic();
			}
			
			for(Symbol* symb : this->get_symbol_table()){
				if (symb->get_symbol_type() == _FUNCTION_){
//					((Function*)symb)->get_function_block()->check_semantic();
					symb->check_semantic_in_symbol();
				}
			}
			
//			std::cout << "for block check pass\n";
		}
		
		
		void run() {
			while(this->condition_expr->evaluate() == "True"){
				for(Element* elem : this->get_elements()){
					elem->run();
				}
				
				this->loop_var_update->run();
			}
			
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
		
		void check_semantic(){
			ValueType condition_type = condition_expression->determine_final_type();
			if (condition_type == _STRING_)
				throw InconsistentTypesError();
			
			for(Element* elem : this->get_elements()){
				elem->check_semantic();
			}
			
			for(Symbol* symb : this->get_symbol_table()){
				if (symb->get_symbol_type() == _FUNCTION_){
//					((Function*)symb)->get_function_block()->check_semantic();
					symb->check_semantic_in_symbol();
				}
			}
			
//			std::cout << "while block check pass\n";
		}
		
		void run() {
			while(this->condition_expression->evaluate() == "True"){
				for(Element* elem : this->get_elements()){
					elem->run();
				}
			}
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
