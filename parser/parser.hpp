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
#include "../exceptions/nebula_exceptions.hpp"


Element* parse_line(std::queue<std::vector<Token> >& program_lines, Block* super_block);
ExpressionStatement* expression_statement_parser(std::vector<Token>& line_tokens, Block* super_block);


std::map<std::string, ValueType> string_to_ValueType_mapping {
	{"void", _VOID_},
	{"string", _STRING_},
	{"integer", _INTEGER_},
	{"decimal", _DECIMAL_},
	{"bool", _BOOLEAN_}
};



//  Regular Expressions for all code elements

std::basic_regex<char> comment_statement_pattern("^(\\$.*)$");
std::basic_regex<char> output_statement_pattern("^(display.*)$");
std::basic_regex<char> input_statement_pattern("^(scan ([a-zA-Z_][a-zA-Z_0-9]*)( , [a-zA-Z_][a-zA-Z_0-9]*)*)$");
std::basic_regex<char> if_statement_pattern("^(if [a-zA-Z0-9._()+*/%>=<! -]+\\{)$");
std::basic_regex<char> else_if_statement_pattern("^(else if [a-zA-Z0-9._()+*/%>=<! -]+\\{)$");
std::basic_regex<char> else_statement_pattern("^(else \\{)$");
std::basic_regex<char> for_statement_pattern("^(for [a-zA-Z_][a-zA-Z0-9_]* from [0-9]+ to [0-9]+( with [0-9]+)? \\{)$");
std::basic_regex<char> while_statement_pattern("^(while [a-zA-Z0-9._()+*/%>=<! -]+\\{)$");
std::basic_regex<char> function_statement_pattern("^(fun [a-zA-Z_][a-zA-Z0-9_]* \\( ([a-zA-Z0-9._()+*/%>=<! -]+ (, [a-zA-Z0-9._()+*/%>=<! -]+)* )?\\) (returns [a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z0-9_]* )?\\{)$");
//std::basic_regex<char> variable_declaration_statement_pattern("^([a-zA-Z_][a-zA-Z0-9_]* [a-zA-Z_][a-zA-Z_0-9]*( = .+)?)$");
std::basic_regex<char> variable_declaration_statement_pattern("^((string|integer|decimal|bool) [a-zA-Z_][a-zA-Z0-9_]*( = .+)?)$");
std::basic_regex<char> variable_assignment_statement_pattern("^([a-zA-Z_][a-zA-Z_0-9]* = .+)$");
std::basic_regex<char> expression_statement_pattern( "^([a-zA-Z0-9.,\"_()+*/%>=<! -]+)$");


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
	
	Token open_bracket_token(_OPEN_BRACKET_LITERAL_, "(", -1,-1);
	Token close_bracket_token(_CLOSE_BRACKET_LITERAL_, ")", -1, -1);
	line_tokens.insert(line_tokens.begin(), open_bracket_token);
	line_tokens.push_back(close_bracket_token);
	
//	int size = line_tokens.size();
	
	std::stack<OperatorNode*> operator_stack;
	std::stack<ExpressionAST*> expression_stack;
	
	OperatorNode* op_node;
//	OperandNodeWithExpression* operand_w_exp;
//	OperandNodeFinal* operand_final;
	OperandNodeWithVariable* operand_w_exp;
	OperandNodeWithConstant* operand_final;
	OperandNodeWithFunctionCall* operand_w_func;
	
//	for (Token& token : line_tokens){
	for (int i=0; i<line_tokens.size(); i++){
//		size--;
		Token& token = line_tokens.at(i);
		TokenType token_type = token.get_token_type();

		if (token_type == _OPEN_BRACKET_LITERAL_){
//			std::cout << "(\n";
			op_node = new OperatorNode(token.get_token_data(), _BRACKET_OP_);
			operator_stack.push( op_node );
		}
		
		else if (token_type == _IDENTIFIER_OR_KEYWORD_LITERAL_){
			if (line_tokens.at(i+1).get_token_type() == _OPEN_BRACKET_LITERAL_){
				Function* function_to_call = (Function*) super_block->find_symbol(line_tokens.at(i).get_token_data());
				if(function_to_call->get_symbol_type() != _FUNCTION_){
					int pos = token.get_position()+token.get_token_data().length();
					line_tokens = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
					throw InvalidSyntaxError(line_tokens, token.get_line_no(), pos);
				}
				
				i+=2; // i at ) or expression's first token
				std::vector<ExpressionAST*> parameters;
				std::vector<Token> param_expression_tokens;
				
				int no_of_open_brackets = 1;
				while( no_of_open_brackets > 0){
					Token& lt = line_tokens.at(i);
					if (lt.get_token_data() == "," && no_of_open_brackets <= 1){
						ExpressionAST* next_param = expression_statement_parser(param_expression_tokens, super_block)->get_expression();
						parameters.push_back(next_param);
						param_expression_tokens.clear();
					}
					else{
						param_expression_tokens.push_back(lt);
						if (lt.get_token_type() == _OPEN_BRACKET_LITERAL_) no_of_open_brackets++;
						if (lt.get_token_type() == _CLOSE_BRACKET_LITERAL_) no_of_open_brackets--;
						
					}

						
					i++; // i at token after )
				}
				i--; // i brought back at ) to let for loop increment it.
				if (param_expression_tokens.size() > 1){
					param_expression_tokens = std::vector<Token>(param_expression_tokens.begin(), param_expression_tokens.end()-1 );
					ExpressionAST* next_param = expression_statement_parser(param_expression_tokens, super_block)->get_expression();
					parameters.push_back(next_param);
				}
				
				operand_w_func = new OperandNodeWithFunctionCall(function_to_call, parameters);
				expression_stack.push(operand_w_func);
				
			}
			else{
				Variable* variable = (Variable*) super_block->find_symbol(token.get_token_data());
				if (variable->get_symbol_type() != _VARIABLE_){
					line_tokens = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
					throw InvalidSyntaxError(line_tokens, token.get_line_no(), token.get_position());
				}
				
				operand_w_exp = new OperandNodeWithVariable(variable);
				expression_stack.push( operand_w_exp );
			}
			
		}
		
		else if (token_type == _INTEGER_LITERAL_ ||
				 token_type == _DECIMAL_LITERAL_ ||
				 token_type == _STRING_LITERAL_ ||
				 token_type == _BOOLEAN_LITERAL_
				 ){
//			std::cout << "operand\n";
			ValueType v_type = TokenType_to_ValueType_mapping.find(token_type)->second;
			operand_final = new OperandNodeWithConstant(v_type, token.get_token_data());
			expression_stack.push( operand_final );
		}				
			
		else if (token_type == _ARITHMETIC_OPERATOR_LITERAL_ ||
				 token_type == _RELATIONAL_OPERATOR_LITERAL_ ||
				 token_type == _LOGICAL_OPERATOR_LITERAL_
				 ){
			
			std::string op_string = token.get_token_data();
			OperatorType op_type = _BINARY_OP_;
			OperatorPrecedence op_precedence = operator_precendence_mapping.find(op_string)->second;
			
//			if (op_string == "not") op_type = _UNARY_OP_;
			if (op_string == "-" || op_string == "not"){
				if (i == 0) op_type = _UNARY_OP_;
				else{
					TokenType t_type = line_tokens.at(i-1).get_token_type();
					if (t_type == _ARITHMETIC_OPERATOR_LITERAL_ ||
						t_type == _RELATIONAL_OPERATOR_LITERAL_ ||
						t_type == _LOGICAL_OPERATOR_LITERAL_ ||
						t_type == _OPEN_BRACKET_LITERAL_)
						op_type = _UNARY_OP_;
				}
			}
			
			if (op_string == "not" && op_type == _BINARY_OP_){
				line_tokens = std::vector<Token> (line_tokens.begin()+1, line_tokens.end()-1);
				throw InvalidSyntaxError(line_tokens, token.get_line_no(), token.get_position()+1);
			}
			
			if (op_type == _UNARY_OP_) op_precedence = _UNARY_MINUS_NOT_;
//			std::cout << token.get_token_data() << ":operator\n";
			
			while( operator_stack.size() > 1 && operator_stack.top()->get_operator_precedence() >= op_precedence && operator_stack.top()->get_operator() != _OPEN_ROUND_BRACKET_OP_){
				op_node = operator_stack.top();
				operator_stack.pop();
				
				ExpressionAST* right_expr = expression_stack.top();
				expression_stack.pop();
				
				ExpressionAST* left_expr = NULL;
				if (op_node->get_operator_type() == _BINARY_OP_){
					if (expression_stack.empty()){
						line_tokens = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
						throw InvalidSyntaxError(line_tokens, line_tokens.at(0).get_line_no(), line_tokens.at(0).get_position());
					}
					
					left_expr = expression_stack.top();
					expression_stack.pop();
				}
					
				op_node->set_left_node(left_expr);
				op_node->set_right_node(right_expr);
				
				expression_stack.push( op_node );
			}
			
			op_node = new OperatorNode(op_string, op_type);
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
					if (expression_stack.empty()){
						line_tokens = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
						throw InvalidSyntaxError(line_tokens, line_tokens.at(0).get_line_no(), line_tokens.at(0).get_position());
					}
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
	
	if (expression_stack.size() == 0){
		line_tokens = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
		throw InvalidSyntaxError(line_tokens, line_tokens.at(0).get_line_no(), line_tokens.at(0).get_position());
	}
	
	ExpressionAST* expression_ast = expression_stack.top();
	expression_stack.pop();
	
	if (expression_stack.size() != 0 || operator_stack.size() != 0){
		line_tokens = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
		throw InvalidSyntaxError(line_tokens, line_tokens.at(0).get_line_no(), line_tokens.at(0).get_position());
	}
	
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
	
	if (type == _VOID_ && type_string != "void"){
		throw InvalidSyntaxError(line_tokens, line_tokens.at(0).get_line_no(), line_tokens.at(0).get_position() );
	}
	
	std::string name = line_tokens.at(1).get_token_data();
	
	ExpressionAST* expression = new OperandNodeWithConstant(type);
	
	if (line_tokens.size() > 2){
		std::vector<Token> expression_tokens(line_tokens.begin()+3, line_tokens.end()); // "=" skipped
		expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
	}
	
	if (super_block->check_symbol_already_exists_in_this_block(name)){
		std::cout << "\nSymbol '" << name << "' already declared before!\n";
		throw std::exception();
	}
	
	Variable* variable = new Variable(type, name, expression);
	super_block->add_symbol(variable);
	
	return new VariableDeclarationStatement (super_block, type, name, expression);
}




VariableAssignmentStatement* variable_assignment_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::string name = line_tokens.at(0).get_token_data();
	
	std::vector<Token> expression_tokens(line_tokens.begin()+2, line_tokens.end());
	ExpressionAST* expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
	
	Variable* symbol = (Variable*) super_block->find_symbol(name);
	symbol->set_value(expression);
	
	return new VariableAssignmentStatement(super_block, name, expression);
}


OutputStatement* output_statement_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	int i=0;
	std::vector<ExpressionAST*> expressions;
		
	std::vector<Token> expression_tokens;
	for(i=1; i<line_tokens.size(); i++){
		Token& lt = line_tokens.at(i);
		if (lt.get_token_data() != ","){
			expression_tokens.push_back(lt);
		}
		else{
			if (expression_tokens.size() < 1){
				int pos = lt.get_position() + 1;
				throw MissingExpressionError(line_tokens, lt.get_line_no(), pos);
			}
			ExpressionAST* expression = expression_statement_parser(expression_tokens, super_block)->get_expression();
			expressions.push_back(expression);
			expression_tokens.clear();
		}
	}
	
	
	if (expression_tokens.size() < 1){
		Token& lt = line_tokens.at(i-1);
		int pos = lt.get_position() + lt.get_token_data().length() + 1;
		throw MissingExpressionError(line_tokens, lt.get_line_no(), pos);
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
		Variable* symbol = (Variable*) super_block->find_symbol(var.get_token_data());
		if (!symbol){
			std::cout << "\nSymbol '" << var.get_token_data() << "' does not exist or accessed before declaration!\n";
			throw std::exception();
		}
		
		variables.push_back(symbol);
	}
	
	return new InputStatement(super_block, variables);
}


IfBlock* if_block_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::vector<Token> expression_in_line = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
	ExpressionAST* condition_expression = expression_statement_parser(expression_in_line, super_block)->get_expression();
	
	IfBlock* if_block = new IfBlock(super_block);
	
	ConditionalBlock* if_condition_block = new ConditionalBlock(if_block, condition_expression);
	
	while(program_lines.front().at(0).get_token_type() != _CLOSE_PARENTHESIS_LITERAL_){ // if 
		
		Element* next_element = parse_line(program_lines, if_condition_block);
		if(next_element)
			if_condition_block->add_element(next_element);
	}
	
	if_block->add_element(if_condition_block);
	program_lines.pop();
	
	
	while( parsable(program_lines.front(), else_if_statement_pattern) ){ // else if
		line_tokens = program_lines.front();
		program_lines.pop();
		expression_in_line = std::vector<Token>(line_tokens.begin()+2, line_tokens.end()-1);
		condition_expression = expression_statement_parser(expression_in_line, super_block)->get_expression();
		
		ConditionalBlock* else_if_condition_block = new ConditionalBlock(if_block, condition_expression);
		
		while(program_lines.front().at(0).get_token_type() != _CLOSE_PARENTHESIS_LITERAL_){
			
			Element* next_element = parse_line(program_lines, else_if_condition_block);
			if(next_element)
				else_if_condition_block->add_element(next_element);
		}
		
		if_block->add_element(else_if_condition_block);
		program_lines.pop();
		
	}
	
	
	line_tokens = program_lines.front(); //else
	if (parsable(line_tokens, else_statement_pattern)){
		program_lines.pop();
		
		ConditionalBlock* else_condition_block = new ConditionalBlock(if_block, NULL);
		
		while(program_lines.front().at(0).get_token_type() != _CLOSE_PARENTHESIS_LITERAL_){
			
			Element* next_element = parse_line(program_lines, else_condition_block);
			if(next_element)
				else_condition_block->add_element(next_element);
		}
		
		if_block->add_element(else_condition_block);
		program_lines.pop();
	}
	
	
	return if_block;
	
	
}



ForBlock* for_block_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::string loop_variable_name = line_tokens.at(1).get_token_data();
	
	int lower_limit = std::stoi(line_tokens.at(3).get_token_data());
	int higher_limit = std::stoi(line_tokens.at(5).get_token_data());
	int step_size = 1;
	
	if (line_tokens.size() > 7){
		step_size = std::stoi(line_tokens.at(7).get_token_data());
	}
	
	ForBlock* for_block = new ForBlock(super_block, loop_variable_name, lower_limit, higher_limit, step_size);
	
	while(program_lines.front().at(0).get_token_type() != _CLOSE_PARENTHESIS_LITERAL_){
		
		Element* next_element = parse_line(program_lines, for_block);
		
		if (next_element)
			for_block->add_element(next_element);
	}
	
	program_lines.pop();
	
	return for_block;
	
}



WhileBlock* while_block_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::vector<Token> expression_in_line = std::vector<Token>(line_tokens.begin()+1, line_tokens.end()-1);
	ExpressionAST* condition_expression = expression_statement_parser(expression_in_line, super_block)->get_expression();
	
	WhileBlock* while_block = new WhileBlock(super_block, condition_expression);
	
	while(program_lines.front().at(0).get_token_type() != _CLOSE_PARENTHESIS_LITERAL_){
		Element* next_element = parse_line(program_lines, while_block);
		if (next_element)
			while_block->add_element(next_element);
	}
	program_lines.pop();
	
	return while_block;
}


Element* function_block_parser(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	std::vector<Token> line_tokens = program_lines.front();
	program_lines.pop();
	
	std::string func_name = line_tokens.at(1).get_token_data();
	
	std::vector<Variable*> parameters;
	
	int i=3; // i at first param-type
	while(line_tokens.at(i).get_token_type() != _CLOSE_BRACKET_LITERAL_){
		
		ValueType param_type = string_to_ValueType_mapping.find(line_tokens.at(i).get_token_data())->second;
		i++; // i at param name
		std::string param_name = line_tokens.at(i).get_token_data();
		OperandNodeWithConstant* param_default_value = new OperandNodeWithConstant(param_type);
		
		Variable* param = new Variable(param_type, param_name, param_default_value);
		
		parameters.push_back(param);
		
		i++; // i at , or )
		if (line_tokens.at(i).get_token_data() == ",") i++; // i at token after , ie a param_type
	}
	
	i++; // i at returns or {
	
	
	ValueType return_type = _VOID_;
	std::string return_variable_name = "";
	if (line_tokens.at(i).get_token_type() != _OPEN_PARENTHESIS_LITERAL_){// i at return type
		i++;
		return_type = string_to_ValueType_mapping.find(line_tokens.at(i).get_token_data())->second;
		return_variable_name = line_tokens.at(++i).get_token_data();
	}
	OperandNodeWithConstant* return_var_default_value = new OperandNodeWithConstant(return_type);
	Variable* return_variable = new Variable(return_type, return_variable_name, return_var_default_value);
	
	
	
	Block* function_block = new Block(super_block);
	for(Variable* param : parameters){
		function_block->add_symbol(param);
	}
	if (return_variable)
		function_block->add_symbol(return_variable);
	
	
	while(program_lines.front().at(0).get_token_type() != _CLOSE_PARENTHESIS_LITERAL_){
		Element* next_element = parse_line(program_lines, function_block);
		if (next_element)
			function_block->add_element(next_element);
	}
	program_lines.pop();
	
	Function* function = new Function(func_name, parameters, return_type, return_variable, function_block);
	
	super_block->add_symbol(function);
	
//	function_block->_repr_();
	return NULL;
}





////////////////////////////////////////////////////////////////////////////////



Element* parse_line(std::queue<std::vector<Token> >& program_lines, Block* super_block){
	
	std::vector<Token> line_tokens = program_lines.front();
	
	
	if (parsable(line_tokens, comment_statement_pattern)){
		program_lines.pop();
		return NULL;
	}
	else if (parsable(line_tokens, output_statement_pattern)){
		return output_statement_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, input_statement_pattern)){
		return input_statement_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, if_statement_pattern)){
		return if_block_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, else_if_statement_pattern)){
		std::cout << "\n'else if' block without if block\n";
		throw std::exception();
	}
	else if (parsable(line_tokens, else_statement_pattern)){
		std::cout << "\n'else' block without if block\n";
		throw std::exception();
	}
	else if (parsable(line_tokens, for_statement_pattern)){
		return for_block_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, while_statement_pattern)){
		return while_block_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, function_statement_pattern)){
		return function_block_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, variable_declaration_statement_pattern)){
		return variable_declaration_statement_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, variable_assignment_statement_pattern)){
		return variable_assignment_statement_parser(program_lines, super_block);
	}
	else if (parsable(line_tokens, expression_statement_pattern)){
		return expression_statement_parser(program_lines, super_block);
	}
	else{		
		throw InvalidSyntaxError(line_tokens, line_tokens.at(0).get_line_no(), line_tokens.at(0).get_position());
	}
}



Block* program_parser(std::queue<std::vector<Token> > program_lines){
	
	Block* program_block = new Block();
	
	Element* next_element = NULL;
	
	while( !program_lines.empty() ){
		
		next_element = parse_line(program_lines, program_block);
		
		if (next_element)
			program_block->add_element(next_element);
		
	}
	
	
	
	
	return program_block;
}




#endif
