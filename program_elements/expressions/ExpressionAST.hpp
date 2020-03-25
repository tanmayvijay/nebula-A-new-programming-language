#ifndef EXPRESSION_AST_H
#define EXPRESSION_AST_H

#include <string>

#include "NodeType.hpp"
#include "../ValueType.hpp"


class ExpressionAST {
	NodeType type;
	
	public:
		//constructor
		ExpressionAST(NodeType type){
			this->type = type;
		}
		
		
		//methods
		NodeType get_node_type();
		
		virtual void _repr_() = 0;
		
		virtual ValueType determine_final_type() = 0;
		
		virtual std::string evaluate() = 0;
		
};


NodeType ExpressionAST::get_node_type(){
	return this->type;
}

#endif

