#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>

#include "Element.hpp"
#include "symbol_table/Symbol.hpp"
#include "expressions/ExpressionAST.hpp"

class Block : public Element{
	std::vector<Element*> sub_elements;
	std::vector<Symbol*> symbol_table;
	Block* super_block = NULL;
	
	public:
		//constructor
		Block(Block* super_block = NULL){
			this->super_block = super_block;
		}

		// methods		
		std::vector<Element*> get_elements();
		
		std::vector<Symbol*> get_symbol_table();
		
		Block* get_super_block();
		
		void add_element(Element* element);
		
		bool add_symbol(Symbol* symbol);
		
		bool check_symbol_already_exists_in_this_block(std::string sym_name);
		
		Symbol* find_symbol(std::string sym_name);
		
		void check_semantic();
		
		
		void run();
		
		void _repr_();
};


//implementations
std::vector<Element*> Block::get_elements(){
	return this->sub_elements;
}


std::vector<Symbol*> Block::get_symbol_table(){
	return this->symbol_table;
}


Block* Block::get_super_block(){
	return this->super_block;
}


void Block::add_element(Element* element){
	this->sub_elements.push_back(element);
}


bool Block::add_symbol(Symbol* symbol){ // returns true if symbol is successfully added to block
	for (Symbol* sym : symbol_table){
		if (sym->get_symbol_name() == symbol->get_symbol_name()){
			std::cout << "\nSymbol : '" << sym->get_symbol_name() << "' alreaady exists!\n";
			throw std::exception();
		}
	}
	this->symbol_table.push_back(symbol);
}


bool Block::check_symbol_already_exists_in_this_block(std::string sym_name){
	for (Symbol* sym : symbol_table){
		if (sym->get_symbol_name() == sym_name){
			return true;
		}
	}
	
	return false;
}


Symbol* Block::find_symbol(std::string sym_name){
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


void Block::check_semantic(){

	for(Element* elem : this->sub_elements){
		elem->check_semantic();
	}
	
	for(Symbol* symb : this->symbol_table){
		if (symb->get_symbol_type() == _FUNCTION_){
			
			symb->check_semantic_in_symbol();
		}
	}
	
	
}


void Block::run(){
	for(Element* elem : this->sub_elements) elem->run();
}


void Block::_repr_(){
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

#endif

