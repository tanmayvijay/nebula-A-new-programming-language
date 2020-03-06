#ifndef PARSER_H
#define PARSER_H

#include<regex>
#include<string>
#include<vector>
#include<exception>
#include<queue>
#include<iostream>
#include<map>
#include<stack>

#include "../program_elements/program_elements.hpp"
#include "../tokenizer/tokenizer.hpp"
#include "../utils/utils.hpp"
#include "../program_elements/variable/variable.hpp"
#include "../program_elements/expression_ast/expression_ast.hpp"


std::map<std::string, ValueType> string_to_ValueType_mapping {
			{"string", _STRING_},
			{"integer", _INTEGER_},
			{"decimal", _DECIMAL_},
			{"bool", _BOOLEAN_}
};


std::basic_regex<char> expression_statement_pattern("^([a-zA-Z0-9_()+-*/%>=<! ]+)$");
std::basic_regex<char> variable_declaration_statement_pattern("^([a-zA-Z_][a-zA-Z_0-9]* [a-zA-Z_][a-zA-Z_0-9]*( = .+)?)$");
std::basic_regex<char> variable_assignment_statement_pattern("^([a-zA-Z_][a-zA-Z_0-9]* = .+)$");


bool parsable(std::vector<Token> line_tokens, std::basic_regex<char> pattern){
	std::string line = "";
	for(Token& lt: line_tokens){
		line = line + lt.get_token_data() + " ";
	}

	line = _trim_from_end_(line);
	return std::regex_match(line, pattern);
}


// when entire line is an expression
ExpressionStatement* expression_statement_parser(std::queue<std::vector<Token> >& program_tokens, Block* super_block){
	
	std::vector<Token> line_tokens = program_tokens.front();
	program_tokens.pop();
	
	Token open_bracket_token(_OPEN_BRACKET_LITERAL_, "(");
	Token close_bracket_token(_CLOSE_BRACKET_LITERAL_, ")");
	line_tokens.insert(line_tokens.begin(), open_bracket_token);
	line_tokens.push_back(close_bracket_token);
	
//	int size = line_tokens.size();
	
	std::stack<OperatorNode*> operator_stack;
	std::stack<ExpressionAST*> expression_stack;
	
	OperatorNode* op_node;
	OperandNode* operand;
	
	for (Token& token : line_tokens){
//		std::cout << token.get_token_data() << std::endl;
//		size--;
		TokenType token_type = token.get_token_type();

		if (token_type == _OPEN_BRACKET_LITERAL_){
//			std::cout << "(\n";
			op_node = new OperatorNode(token);
			operator_stack.push( op_node );
		}
		
		else if (token_type == _NUMBER_LITERAL_ || token_type == _STRING_LITERAL_ ||
				token_type == _IDENTIFIER_OR_KEYWORD_LITERAL_){
//			std::cout << "operand\n";
			operand = new OperandNode(token);
			expression_stack.push( operand );
		}				
			
		else if (token_type == _ARITHMETIC_OPERATOR_LITERAL_ || token_type == _RELATIONAL_OPERATOR_LITERAL_ || token_type == _LOGICAL_OPERATOR_LITERAL_){
//			std::cout << token.get_token_data() << ":operator\n";
			OperatorPrecedence op_precedence = operator_precendence_mapping.find(token.get_token_data())->second;
			while( operator_stack.size() > 1 && operator_stack.top()->get_operator_precedence() >= op_precedence && operator_stack.top()->get_node_data().get_token_type() != _OPEN_BRACKET_LITERAL_){
				op_node = operator_stack.top();
				operator_stack.pop();
				
				ExpressionAST* right_expr = expression_stack.top();
				expression_stack.pop();
				
				ExpressionAST* left_expr = NULL;
				if (op_node->get_operator_type() == _BINARY_OP_){
					left_expr = expression_stack.top();
					expression_stack.pop();
				}
					
				op_node->set_left_node(left_expr);
				op_node->set_right_node(right_expr);
				
				expression_stack.push( op_node );
			}
			
			op_node = new OperatorNode(token);
			operator_stack.push( op_node);
		}
		
		else if(token_type == _CLOSE_BRACKET_LITERAL_){
//			std::cout << ")\n" << size << "\n";
			while( operator_stack.size() > 1 && operator_stack.top()->get_node_data().get_token_type() != _OPEN_BRACKET_LITERAL_){
				op_node = operator_stack.top();
				operator_stack.pop();
				
//				std::cout << op_node->get_node_data().get_token_data() << "\n";
				
//				std::cout << expression_stack.size() << "\n";

//				std::cout << "here\n";
				ExpressionAST* right_expr = expression_stack.top();
				expression_stack.pop();
				
				ExpressionAST* left_expr = NULL;

				if (op_node->get_operator_type() == _BINARY_OP_){
					left_expr = expression_stack.top();
					expression_stack.pop();
				}

				
				op_node->set_left_node(left_expr);
				op_node->set_right_node(right_expr);
				
				expression_stack.push( op_node );
				
			}
			
			operator_stack.pop();
//			std::cout << operator_stack.top()->get_node_data().get_token_data() << "\n";
			
		}
		
		else{
			throw std::exception();
		}
	}
	
	ExpressionAST* expression_ast = expression_stack.top();
	expression_stack.pop();
//	expression_ast->_repr_();
	return new ExpressionStatement(super_block, expression_ast);
}


// when only line subpart is an expression
ExpressionStatement* expression_statement_parser(std::vector<Token>& line_tokens, Block* super_block){
	std::queue<std::vector<Token> > expression_tokens_queue;
	expression_tokens_queue.push(line_tokens);
	
	return expression_statement_parser(expression_tokens_queue, super_block);
}




VariableDeclarationStatement* variable_declaration_statement_parser(std::queue<std::vector<Token> >& program_tokens, Block* super_block){
	std::vector<Token> line_tokens = program_tokens.front();
	program_tokens.pop();
	
	std::string type_string = line_tokens.at(0).get_token_data();
	ValueType type = string_to_ValueType_mapping.find(type_string)->second;
	
	std::string name = line_tokens.at(1).get_token_data();
	
	ExpressionStatement* expression = NULL;
	
	if (line_tokens.size() > 2){
		std::vector<Token> expression_tokens(line_tokens.begin()+3, line_tokens.end()); // "=" skipped
		expression = expression_statement_parser(expression_tokens, super_block);
	}
	
	return new VariableDeclarationStatement (super_block, type, name, expression);
}




VariableAssignmentStatement* variable_assignment_statement_parser(std::queue<std::vector<Token> >& program_tokens, Block* super_block){
	std::vector<Token> line_tokens = program_tokens.front();
	program_tokens.pop();
	
	std::string name = line_tokens.at(0).get_token_data();
	
	std::vector<Token> expression_tokens(line_tokens.begin()+2, line_tokens.end());
	ExpressionStatement* expression = expression_statement_parser(expression_tokens, super_block);
	
	
	return new VariableAssignmentStatement(super_block, name, expression);
}

////////////////////////////////////////////////////////////////////////////////




std::vector<Element*>* program_parser(std::queue<std::vector<Token> > program_tokens){

	std::vector<Element*>* program_elements = new std::vector<Element*>();
	
	Element* next_element = NULL;
	
	while( !program_tokens.empty() ){
		
		std::vector<Token> line_tokens = program_tokens.front();

		next_element = NULL;
		
		bool line_parsed = false;

		if (parsable(line_tokens, variable_declaration_statement_pattern)){
			next_element = variable_declaration_statement_parser(program_tokens, NULL);
//			next_element->_repr_();
			
			line_parsed = true;
		}
		else if (parsable(line_tokens, variable_assignment_statement_pattern)){
			next_element = variable_assignment_statement_parser(program_tokens, NULL);
//			next_element->_repr_();
			line_parsed = true;
		}
		else if (parsable(line_tokens, expression_statement_pattern)){
			
			next_element = expression_statement_parser(program_tokens, NULL);
//			std::cout << "here\n";
//			next_element->_repr_();
			line_parsed = true;
		}
		
		if (!line_parsed){
			std::cout << "\nline not parsed\n";

			throw std::exception();
		}
		
//		next_element->_repr_();
		
//		std::cout << "\n\n\n##########################################";
//		for(Element* e : *program_elements){
//			e->_repr_();
//		}
		
		program_elements->push_back(next_element);
		
	}
	
	
	
	
	return program_elements;
//	return new Block(program_elements);
}




#endif
