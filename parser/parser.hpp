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
#include "../program_elements/value_type.hpp"
#include "../program_elements/expression_ast/expression_ast.hpp"
#include "../program_elements/symbol_table/symbol_table.hpp"


std::map<std::string, ValueType> string_to_ValueType_mapping {
			{"string", _STRING_},
			{"integer", _INTEGER_},
			{"decimal", _DECIMAL_},
			{"bool", _BOOLEAN_}
};



//  Regular Expressions for all code elements

std::basic_regex<char> comment_statement_pattern("^(\\$.*)$");
std::basic_regex<char> output_statement_pattern("^(display ([^,]+)( , [^,]+)*)$");
std::basic_regex<char> input_statement_pattern("^(scan ([a-zA-Z_][a-zA-Z_0-9]*)( , [a-zA-Z_][a-zA-Z_0-9]*)*)$");
std::basic_regex<char> variable_declaration_statement_pattern("^([a-zA-Z_][a-zA-Z_0-9]* [a-zA-Z_][a-zA-Z_0-9]*( = .+)?)$");
std::basic_regex<char> variable_assignment_statement_pattern("^([a-zA-Z_][a-zA-Z_0-9]* = .+)$");
std::basic_regex<char> expression_statement_pattern( "^([a-zA-Z0-9._()+-*/%>=<! ]+)$");

//  End of Regular Expressions for all code elements



bool parsable(std::vector<Token> line_tokens, std::basic_regex<char> pattern){
	std::string line = "";
	for(Token& lt: line_tokens){
			line = line + lt.get_token_data() + " ";
	}

	line = _trim_from_end_(line);
	return std::regex_match(line, pattern);
}



std::map<TokenType, ValueType> TokenType_to_ValueType_mapping{
	{_INTEGER_LITERAL_, _INTEGER_},
	{_DECIMAL_LITERAL_, _DECIMAL_},
	{_STRING_LITERAL_, _STRING_},
	{_BOOLEAN_LITERAL_, _BOOLEAN_}
};

// when entire line is an expression
ExpressionStatement* expression_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	Token open_bracket_token(_OPEN_BRACKET_LITERAL_, "(");
	Token close_bracket_token(_CLOSE_BRACKET_LITERAL_, ")");
	line_tokens.insert(line_tokens.begin(), open_bracket_token);
	line_tokens.push_back(close_bracket_token);
	
//	int size = line_tokens.size();
	
	std::stack<OperatorNode*> operator_stack;
	std::stack<ExpressionAST*> expression_stack;
	
	OperatorNode* op_node;
	OperandNodeWithExpression* operand_w_exp;
	OperandNodeFinal* operand_final;
	
	for (Token& token : line_tokens){
//		std::cout << token.get_token_data() << std::endl;
//		size--;
		TokenType token_type = token.get_token_type();

		if (token_type == _OPEN_BRACKET_LITERAL_){
//			std::cout << "(\n";
			op_node = new OperatorNode(token.get_token_data());
			operator_stack.push( op_node );
		}
		
		else if (token_type == _IDENTIFIER_OR_KEYWORD_LITERAL_){
			Symbol* symbol = super_block->find_symbol(token.get_token_data());
			operand_w_exp = new OperandNodeWithExpression(symbol->get_value_type(), symbol->get_symbol_value());
			expression_stack.push( operand_w_exp );
		}
		
		else if (token_type == _INTEGER_LITERAL_ ||
				 token_type == _DECIMAL_LITERAL_ ||
				 token_type == _STRING_LITERAL_ ||
				 token_type == _BOOLEAN_LITERAL_
				 ){
//			std::cout << "operand\n";
			ValueType v_type = TokenType_to_ValueType_mapping.find(token_type)->second;
			operand_final = new OperandNodeFinal(v_type, token.get_token_data());
			expression_stack.push( operand_final );
		}				
			
		else if (token_type == _ARITHMETIC_OPERATOR_LITERAL_ ||
				 token_type == _RELATIONAL_OPERATOR_LITERAL_ ||
				 token_type == _LOGICAL_OPERATOR_LITERAL_
				 ){
//			std::cout << token.get_token_data() << ":operator\n";
			OperatorPrecedence op_precedence = operator_precendence_mapping.find(token.get_token_data())->second;
			while( operator_stack.size() > 1 && operator_stack.top()->get_operator_precedence() >= op_precedence && operator_stack.top()->get_operator() != _OPEN_ROUND_BRACKET_OP_){
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
			
			op_node = new OperatorNode(token.get_token_data());
			operator_stack.push( op_node);
		}
		
		else if(token_type == _CLOSE_BRACKET_LITERAL_){
//			std::cout << ")\n" << size << "\n";
			while( operator_stack.size() > 1 && operator_stack.top()->get_operator() != _OPEN_ROUND_BRACKET_OP_){
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
			std::cout << "Expression cannot be parse at token: '" << token.get_token_data() << "'\n";
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




VariableDeclarationStatement* variable_declaration_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::string type_string = line_tokens.at(0).get_token_data();
	ValueType type = string_to_ValueType_mapping.find(type_string)->second;
	
	std::string name = line_tokens.at(1).get_token_data();
	
	ExpressionAST* expression = NULL;
	
	if (line_tokens.size() > 2){
		std::vector<Token> expression_tokens(line_tokens.begin()+3, line_tokens.end()); // "=" skipped
		expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
	}
	
	if (super_block->check_symbol_already_exists_in_this_block(name)){
		std::cout << "\nSymbol '" << name << "' already declared before!\n";
		throw std::exception();
	}
	
	Symbol* symbol = new Symbol(type, name, expression);
	super_block->add_symbol(symbol);
	
	return new VariableDeclarationStatement (super_block, type, name, expression);
}




VariableAssignmentStatement* variable_assignment_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::string name = line_tokens.at(0).get_token_data();
	
	std::vector<Token> expression_tokens(line_tokens.begin()+2, line_tokens.end());
	ExpressionAST* expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
	
	Symbol* symbol = super_block->find_symbol(name);
	symbol->set_value(expression);
	
	return new VariableAssignmentStatement(super_block, name, expression);
}


OutputStatement* output_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
//	for (Token& t : line_tokens){
//		std::cout << "'" << t.get_token_data() << "' ";
//	}
//	std::cout << "\n";
	
	std::vector<ExpressionAST*> expressions;
		
	std::vector<Token> expression_tokens;
	for(int i=1; i<line_tokens.size(); i++){
		Token& lt = line_tokens.at(i);
		if (lt.get_token_data() != ","){
			expression_tokens.push_back(lt);
		}
		else{
			ExpressionAST* expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
			expressions.push_back(expression);
			expression_tokens.clear();
		}
	}
	ExpressionAST* expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
	expressions.push_back(expression);
	
	return new OutputStatement(super_block, expressions);
}


InputStatement* input_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::vector<Symbol*> variables;
	
	for(int i=1; i<line_tokens.size(); i+=2 ){ // skip 'scan' token and then skip alternate ',' tokens
		Token& var = line_tokens.at(i);
		Symbol* symbol = super_block->find_symbol(var.get_token_data());
		if (!symbol){
			std::cout << "\nSymbol '" << var.get_token_data() << "' does not exist or accessed before declaration!\n";
			throw std::exception();
		}
		
		variables.push_back(symbol);
	}
	
	return new InputStatement(super_block, variables);
}

////////////////////////////////////////////////////////////////////////////////




Block* program_parser(std::queue<std::vector<Token> > program_lines){
	
	Block* program_block = new Block();
	
	Element* next_element = NULL;
	
	while( !program_lines.empty() ){
		
		std::vector<Token> line_tokens = program_lines.front();

		next_element = NULL;
		
		bool line_parsed = false;
		
		if (parsable(line_tokens, comment_statement_pattern)){
//			next_element = comment_statement_parser(program_lines, NULL);
			program_lines.pop();
			continue;
		}
		else if (parsable(line_tokens, output_statement_pattern)){
			next_element = output_statement_parser(program_lines, program_block);
			line_parsed = true;
		}
		else if (parsable(line_tokens, input_statement_pattern)){
			next_element = input_statement_parser(program_lines, program_block);
			line_parsed = true;
		}
		else if (parsable(line_tokens, variable_declaration_statement_pattern)){
			next_element = variable_declaration_statement_parser(program_lines, program_block);
			line_parsed = true;
		}
		else if (parsable(line_tokens, variable_assignment_statement_pattern)){
			next_element = variable_assignment_statement_parser(program_lines, program_block);
			line_parsed = true;
		}
		else if (parsable(line_tokens, expression_statement_pattern)){
			
			next_element = expression_statement_parser(program_lines, program_block);
			line_parsed = true;
		}
		
		if (!line_parsed){
			std::cout << "\nline not parsed\n";	
			throw std::exception();
		}
		
		program_block->add_element(next_element);
		
	}
	
	
	
	
	return program_block;
}




#endif
