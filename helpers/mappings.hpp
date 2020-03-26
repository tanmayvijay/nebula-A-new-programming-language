#ifndef MAPPINGS_H
#define MAPPINGS_H

#include <map>

#include "../program_elements/ValueType.hpp"
#include "../tokenizer/TokenType.hpp"
#include "../program_elements/expressions/OperatorPrecedence.hpp"
#include "../program_elements/expressions/Operator.hpp"


std::map<std::string, ValueType> string_to_ValueType_mapping {
	{"void", _VOID_},
	{"string", _STRING_},
	{"integer", _INTEGER_},
	{"double", _DOUBLE_},
	{"bool", _BOOLEAN_}
};


std::map<TokenType, ValueType> TokenType_to_ValueType_mapping{
	{_INTEGER_LITERAL_, _INTEGER_},
	{_DOUBLE_LITERAL_, _DOUBLE_},
	{_STRING_LITERAL_, _STRING_},
	{_BOOLEAN_LITERAL_, _BOOLEAN_}
};


std::map<std::string, OperatorPrecedence> operator_precendence_mapping {
	{"or", _OR_},
	{"and", _AND_},
	{"==", _IS_EQUAL_IS_NOT_EQUAL_},
	{"!=", _IS_EQUAL_IS_NOT_EQUAL_},
	{">", _GT_GTE_LT_LTE_},
	{">=", _GT_GTE_LT_LTE_},
	{"<", _GT_GTE_LT_LTE_},
	{"<=", _GT_GTE_LT_LTE_},
	{"+", _PLUS_MINUS_},
	{"-", _PLUS_MINUS_},
	{"*", _MULTIPLY_DIVIDE_MODULUS_},
	{"/", _MULTIPLY_DIVIDE_MODULUS_},
	{"%", _MULTIPLY_DIVIDE_MODULUS_},
	{"**", _POWER_},
	{"not", _UNARY_MINUS_NOT_},
	{"[", _SQUARE_BRACKET_},
	{"(", _BRACKET_}
	
};



std::map<std::string, Operator> string_to_operator_mapping {
	{"or", _OR_OP_},
	{"and", _AND_OP_},
	{"==", _EQUAL_OP_},
	{"!=", _NOT_EQUAL_OP_},
	{">", _GT_OP_},
	{">=", _GTE_OP_},
	{"<", _LT_OP_},
	{"<=", _LTE_OP_},
	{"+", _PLUS_OP_},
	{"-", _MINUS_OP_},
	{"*", _MULTIPLY_OP_},
	{"/", _DIVIDE_OP_},
	{"%", _MODULUS_OP_},
	{"**", _POWER_OP_},
	{"not", _NOT_OP_},
	{"[", _OPEN_SQUARE_BRACKET_OP_},
	{"(", _OPEN_ROUND_BRACKET_OP_}
	
};


std::map<ValueType, std::string> ValueType_to_default_value_mapping {
	{_VOID_, "N/A"},
	{_INTEGER_, "0"},
	{_DOUBLE_, "0.0"},
	{_STRING_, ""},
	{_BOOLEAN_, "False"},
	{_CUSTOM_, ""}
};

#endif

