#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<string>
#include<iostream>
#include<map>

#include "../variable/variable.hpp"
#include "../../tokenizer/tokenizer.hpp"


enum NodeType{
	_OPERATOR_NODE_,
	_OPERAND_NODE_
};


class ExpressionAST {
	NodeType type;
	Token node_data = Token(_OTHER_TOKEN_LITERAL_, "");
	
	public:
		ExpressionAST(NodeType type, Token& node_data){
			this->type = type;
			this->node_data = node_data;
		}
		
		NodeType get_node_type(){
			return this->type;
		}
		
		Token get_node_data(){
			return this->node_data;
		}
		
		virtual void _repr_() = 0;
		
};


enum OperatorType{
	_BINARY_OPERATOR_,
	_UNARY_OPERATOR_
};


enum OperatorPrecedence{
	_PLUS_MINUS_,
	_MULTIPLY_DIVIDE_,
	_MODULUS_,
	_BRACKET_
};

std::map<std::string, OperatorPrecedence> operator_precendence_mapping {
			{"+", _PLUS_MINUS_},
			{"-", _PLUS_MINUS_},
			{"*", _MULTIPLY_DIVIDE_},
			{"/", _MULTIPLY_DIVIDE_},
			{"%", _MODULUS_},
			{"(", _BRACKET_}
};




class OperatorNode : public ExpressionAST{
	ExpressionAST* left_node = NULL;
	ExpressionAST* right_node = NULL;
	
	OperatorPrecedence precedence;
	
//	OperatorType operator_type; // binary or unary
	
	public:
		OperatorNode(Token& node_data) : ExpressionAST(_OPERATOR_NODE_, node_data){
			this->precedence = operator_precendence_mapping.find(node_data.get_token_data())->second;
		}
		
		OperatorPrecedence get_operator_precedence(){
			return this->precedence;
		}

		
		ExpressionAST* get_left_node(){
			return this->left_node;
		}
		
		ExpressionAST* get_right_node(){
			return this->right_node;
		}
		
		void set_left_node(ExpressionAST* node){
			this->left_node = node;
		}
		
		void set_right_node(ExpressionAST* node){
			this->right_node = node;
		}
		
		
		void _repr_(){
			std::cout << "[";
			
			this->left_node->_repr_();
			
			std::cout << " " << this->get_node_data().get_token_data() << " ";
			
			this->right_node->_repr_();
			
			std::cout << "] ";
		}
			
};


class OperandNode : public ExpressionAST{
	public:
		OperandNode(Token& node_data) : ExpressionAST(_OPERAND_NODE_, node_data){
			
		}
		
		void _repr_(){
			std::cout << this->get_node_data().get_token_data();
		}
		
	
};








//
//class ArithmaticExpression : public ExpressionAST{
//	
//};
//
//class RelationalExpression : public ExpressionAST{
//	
//};
//
//class LogicalExpression : public ExpressionAST{
//	
//};
//
//class ConditionalExpression : public ExpressionAST{
//	
//};
//


#endif
