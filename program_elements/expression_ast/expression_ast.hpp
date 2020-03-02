#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<string>
#include "../variable/variable.hpp"


enum NodeType{
	_OPERATOR_NODE_,
	_OPERAND_NODE_
};


class ExpressionAST{
	NodeType type;
	
	public:
		ExpressionAST(NodeType type){
			this->type = type;
		}
		
		virtual void _repr_() = 0;
		
};


enum OperatorType{
	_BINARY_OPERATOR_,
	_UNARY_OPERATOR_
};

enum Operator{
	_PLUS_,
	_MINUS_,
	_MULTIPLY_,
	_DIVIDE_,
	_MODULUS_,
	_POWER_,
};

class OperatorNode : public ExpressionAST{
	ExpressionAST* left_node;
	ExpressionAST* right_node;
	
	OperatorType operator_type; // binary or unary
	
	Operator op; // Actual operator
	
	public:
		OperatorNode(OperatorType operator_type, Opreator op) : ExpressionAST(_OPERATOR_NODE_){
			this->operator_type = operator_type;
			this->op = op;
		}
		
		OperatorType get_operator_type(){
			return this->operator_type;
		}
		
		Operator get_operator(){
			return this->op;
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
			this->left_node->_repr_();
			
			std::cout << " " << 
			
			this->right_node->_repr_();
		}
			
};


class OperandNode : public ExpressionAST{
	ValueHolder* value_holder;
	
	public:
		OperandNode(ValueHolder* value_holder) : ExpressionAST(_OPERAND_NODE_){
			this->value_holder = value_holder
		}
		
		ValueHolder* get_value_holder(){
			return this->get_value_holder;
		}
		
		
		void _repr_(){
			std::cout << " " << this->value_holder->get_value(); 
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
