#ifndef OPERATOR_NODE_H
#define OPERATOR_NODE_H

#include <iostream>
#include <cmath>

#include "ExpressionAST.hpp"
#include "Operator.hpp"
#include "OperatorType.hpp"
#include "OperatorPrecedence.hpp"
#include "../../helpers/mappings.hpp"


class OperatorNode : public ExpressionAST{
	Operator op;
	
	ExpressionAST* left_node = NULL;
	ExpressionAST* right_node = NULL;
	
	OperatorType operator_type;
	
	OperatorPrecedence precedence;
	
	public:
		//constructor
		OperatorNode(std::string op_string, OperatorType op_type) : ExpressionAST(_OPERATOR_NODE_){
			this->op = string_to_operator_mapping.find(op_string)->second;
			this->operator_type = op_type;
			this->precedence = operator_precendence_mapping.find(op_string)->second;
			if (this->operator_type == _UNARY_OP_) this->precedence = _UNARY_MINUS_NOT_;
		}
		
		
		//methods
		Operator get_operator();
		
		OperatorPrecedence get_operator_precedence();
		
		OperatorType get_operator_type();

		
		ExpressionAST* get_left_node();
		
		ExpressionAST* get_right_node();
		
		void set_left_node(ExpressionAST* node);
		
		void set_right_node(ExpressionAST* node);
		
		ValueType determine_final_type();
		
		std::string evaluate();

		void _repr_();
			
};

//implementations
Operator OperatorNode::get_operator(){
	return this->op; 
}


OperatorPrecedence OperatorNode::get_operator_precedence(){
	return this->precedence;
}


OperatorType OperatorNode::get_operator_type(){
	return this->operator_type;
}


ExpressionAST* OperatorNode::get_left_node(){
	return this->left_node;
}


ExpressionAST* OperatorNode::get_right_node(){
	return this->right_node;
}


void OperatorNode::set_left_node(ExpressionAST* node){
	this->left_node = node;
}

void OperatorNode::set_right_node(ExpressionAST* node){
	this->right_node = node;
}


ValueType OperatorNode::determine_final_type(){ // this automatically does check semantic of the expression
	ValueType r_type = this->right_node->determine_final_type();
	
	
	if ( !this->left_node && this->op == _MINUS_OP_)
		if (r_type == _INTEGER_ || r_type == _DOUBLE_) return r_type;
	
	
	if (!this->left_node && this->op == _NOT_OP_){
		if (r_type == _STRING_){
			std::cerr << "Inconsistent Types Error: " << r_type << " is not string.";
			throw std::exception();
		}
		
		return _BOOLEAN_;
	}
	
	ValueType l_type = this->left_node->determine_final_type();
	
	
	for(Operator op : {_AND_OP_, _OR_OP_})
		if (this->op == op){
			
			if (l_type == _STRING_ || r_type == _STRING_){
				std::cerr << "Inconsistent Types Error: string operand is not supported.";
				throw std::exception();
			}
			
			return _BOOLEAN_;
		}
	
	
	for(Operator op : {_EQUAL_OP_, _NOT_EQUAL_OP_})
		if (this->op == op){
			if ( (l_type == _BOOLEAN_ || l_type == _INTEGER_ || l_type == _DOUBLE_) && 
				(r_type == _BOOLEAN_ || r_type == _INTEGER_ || r_type == _DOUBLE_) ) return _BOOLEAN_;
			
			else if (l_type  == r_type) return _BOOLEAN_;
			
			else{
				std::cerr << "Inconsistent Types Error: " << this->op << " does not support " << r_type << " with " << l_type << ".";
				throw std::exception();
			}
		}
			
	
	
	for(Operator op : {_GT_OP_, _GTE_OP_, _LT_OP_, _LTE_OP_})
		if (this->op == op){
			if (l_type == _STRING_ || l_type == _BOOLEAN_ || r_type == _STRING_ || r_type == _BOOLEAN_){
				std::cerr << "Inconsistent Types Error: Only integer and double types are supported";
				throw std::exception();
			}
			return _BOOLEAN_;
		}
	
	
	if (this->op == _MODULUS_OP_){
		
		if (l_type == _INTEGER_ && r_type == _INTEGER_) return _INTEGER_;
		
		std::cerr << "Inconsistent Types Error: Only integer type supported in modulus.";
		throw std::exception();
	}
	
	if (this->op == _POWER_OP_){
		if ((l_type == _INTEGER_ || l_type == _DOUBLE_) && (r_type == _INTEGER_ || r_type == _DOUBLE_)){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_) return _DOUBLE_;
			return _INTEGER_;
		}
	}
		
	
	
	if (this->op == _PLUS_OP_){
		if (l_type == _STRING_ && r_type == _STRING_)
			return _STRING_;
	}
	
	 // - / and *
	if (l_type == _INTEGER_ && r_type == _INTEGER_) return _INTEGER_;
	
	if ((l_type == _DOUBLE_ && (r_type == _DOUBLE_ || r_type == _INTEGER_)))
		return _DOUBLE_;
		
	if ((r_type == _DOUBLE_ && (l_type == _DOUBLE_ || l_type == _INTEGER_)))
		return _DOUBLE_;
	
		
	std::cerr << "Inconsistent Types Error: " << this->op << " does not support " << r_type << " with " << l_type << ".";
	throw std::exception();
	
	
}


std::string OperatorNode::evaluate(){
	
	std::string r_value = this->right_node->evaluate();
	ValueType r_type = this->right_node->determine_final_type();
	if (this->operator_type == _UNARY_OP_){
		
		if (this->op == _MINUS_OP_){
			if (r_type == _INTEGER_){
				int r_value_temp = std::stoi(r_value);
				r_value_temp = -r_value_temp;
				return std::to_string(r_value_temp);
			}
			else{ // if r_type is _DOUBLE_
				double r_value_temp = std::stod(r_value);
				r_value_temp = -r_value_temp;
				return std::to_string(r_value_temp);
			}
		}
		else{ //if(this->op == _NOT_OP_)
			if (r_type == _INTEGER_){
				int r_value_temp = std::stoi(r_value);
				if (r_value_temp) return "False";
				return "True";
			}
			if (r_type == _DOUBLE_){
				double r_value_temp = std::stod(r_value);
				if(r_value_temp) return "False";
				return "True";
			}
			else{ // in case of _BOOLEAN_
				if (r_value == "True") return "False";
				else return "True";
			}
			
		} 
	}
	else{ // in case of binary operator
		std::string l_value = this->left_node->evaluate();
		ValueType l_type = this->left_node->determine_final_type();
	
		if (this->op == _PLUS_OP_){
			if (l_type == _STRING_ && r_type == _STRING_) return l_value + r_value;
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				double ans = l_value_temp + r_value_temp;
				return std::to_string(ans);
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			int ans = l_value_temp + r_value_temp;
			return std::to_string(ans);
		}
		
		if (this->op == _MINUS_OP_){
			
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				double ans = l_value_temp - r_value_temp;
				return std::to_string(ans);
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			int ans = l_value_temp - r_value_temp;
			return std::to_string(ans);
		}
		
		if (this->op == _MULTIPLY_OP_){
			
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				double ans = l_value_temp * r_value_temp;
				return std::to_string(ans);
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			int ans = l_value_temp * r_value_temp;
			return std::to_string(ans);
		}
		
		if (this->op == _DIVIDE_OP_){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				double ans = l_value_temp / r_value_temp;
				return std::to_string(ans);
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			int ans = l_value_temp / r_value_temp;
			return std::to_string(ans);
		}
		
		if (this->op == _MODULUS_OP_){
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			int ans = l_value_temp % r_value_temp;
			return std::to_string(ans);
		}
		
		if (this->op == _POWER_OP_){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				double ans = pow(l_value_temp, r_value_temp);
				return std::to_string(ans);
			}
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			int ans = pow(l_value_temp, r_value_temp);
			return std::to_string(ans);
		}
		
		if (this->op == _EQUAL_OP_){
			if (l_type == _STRING_ && r_type == _STRING_){
				if (l_value == r_value) return "True";
				else return "False";
			}
			if (l_type == _BOOLEAN_ && r_type == _BOOLEAN_){
				if (l_value == r_value) return "True";
				else return "False";
			}
			else if (l_type == _BOOLEAN_){
				std::string r_value_temp = "False";
				if (std::stod(r_value) != 0) r_value_temp = "True"; 
				
				if (l_value == r_value_temp ) return "True";
				return "False";
			}
			else if (r_type == _BOOLEAN_){
				std::string l_value_temp = "False";
				if (std::stod(l_value) != 0) l_value_temp = "True"; 
				
				if (l_value_temp == r_value ) return "True";
				return "False";
			}
			else{
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				
				if (l_value_temp == r_value_temp) return "True";
				return "False";
			}
		}
		if (this->op == _NOT_EQUAL_OP_){
			if (l_type == _STRING_ && r_type == _STRING_){
				if (l_value != r_value) return "True";
				else return "False";
			}
			if (l_type == _BOOLEAN_ && r_type == _BOOLEAN_){
				if (l_value != r_value) return "True";
				else return "False";
			}
			else if (l_type == _BOOLEAN_){
				std::string r_value_temp = "False";
				if (std::stod(r_value) != 0) r_value_temp = "True"; 
				
				if (l_value != r_value_temp ) return "True";
				return "False";
			}
			else if (r_type == _BOOLEAN_){
				std::string l_value_temp = "False";
				if (std::stod(l_value) != 0) l_value_temp = "True"; 
				
				if (l_value_temp != r_value ) return "True";
				return "False";
			}
			else{
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				
				if (l_value_temp != r_value_temp) return "True";
				return "False";
			}
		}
		
		if (this->op == _GTE_OP_){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				bool ans = l_value_temp >= r_value_temp;
				if (ans) return "True";
				return "False";
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			bool ans = l_value_temp >= r_value_temp;
			if (ans) return "True";
			return "False";
		}
		
		if (this->op == _GT_OP_){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				bool ans = l_value_temp > r_value_temp;
				if (ans) return "True";
				return "False";
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			bool ans = l_value_temp > r_value_temp;
			if (ans) return "True";
			return "False";
		}
		
		if (this->op == _LTE_OP_){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				bool ans = l_value_temp <= r_value_temp;
				if (ans) return "True";
				return "False";
			}
//			std::cout << l_value << "\nlte-here\n";
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			bool ans = l_value_temp <= r_value_temp;
			if (ans) return "True";
			return "False";
		}
		
		if (this->op == _LT_OP_){
			if (l_type == _DOUBLE_ || r_type == _DOUBLE_){
				double l_value_temp = std::stod(l_value);
				double r_value_temp = std::stod(r_value);
				bool ans = l_value_temp < r_value_temp;
				if (ans) return "True";
				return "False";
			}
			
			int l_value_temp = std::stoi(l_value);
			int r_value_temp = std::stoi(r_value);
			bool ans = l_value_temp < r_value_temp;
			if (ans) return "True";
			return "False";
		}
		
		if (this->op == _AND_OP_){
			bool l_value_temp;
			bool r_value_temp;
			
			if (l_type == _BOOLEAN_){
				if (l_value == "True") l_value_temp = true;
				else l_value_temp = false;
			}
			else if (l_type == _INTEGER_){
				if (std::stoi(l_value) ) l_value_temp = true;
				else l_value_temp = false;
			}
			else { // l_type is _DOUBLE_
				if (std::stod(l_value) ) l_value_temp = true;
				else l_value_temp = false;
			}
			
			if (r_type == _BOOLEAN_){
				if (r_value == "True") r_value_temp = true;
				else r_value_temp = false;
			}
			else if (r_type == _INTEGER_){
				if (std::stoi(r_value) ) r_value_temp = true;
				else r_value_temp = false;
			}
			else { // r_type is _DOUBLE_
				if (std::stod(r_value) ) r_value_temp = true;
				else r_value_temp = false;
			}
//					std::cout << l_value_temp << r_value_temp;
			
			if (l_value_temp && r_value_temp) return "True";
			return "False";
			
		}
		if (this->op == _OR_OP_){
			bool l_value_temp;
			bool r_value_temp;
			
			if (l_type == _BOOLEAN_){
				if (l_value == "True") l_value_temp = true;
				else l_value_temp = false;
			}
			else if (l_type == _INTEGER_){
				if (std::stoi(l_value) ) l_value_temp = true;
				else l_value_temp = false;
			}
			else { // l_type is _DOUBLE_
				if (std::stod(l_value) ) l_value_temp = true;
				else l_value_temp = false;
			}
			
			if (r_type == _BOOLEAN_){
				if (r_value == "True") r_value_temp = true;
				else r_value_temp = false;
			}
			else if (r_type == _INTEGER_){
				if (std::stoi(r_value) ) r_value_temp = true;
				else r_value_temp = false;
			}
			else { // r_type is _DOUBLE_
				if (std::stod(r_value) ) r_value_temp = true;
				else r_value_temp = false;
			}
			
			if (l_value_temp || r_value_temp) return "True";
			return "False";
		}
	}
	
	
	
	
}


void OperatorNode::_repr_(){
//			std::cout << "{" << this->determine_final_type() <<"} [ ";
	std::cout << " [ ";
	
	if (this->left_node)
		this->left_node->_repr_();
	
	std::cout << " " << this->op << " ";
	
	this->right_node->_repr_();
	
	std::cout << " ] ";
}


#endif

