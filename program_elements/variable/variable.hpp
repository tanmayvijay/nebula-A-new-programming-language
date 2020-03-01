#ifndef VARIABLE_H
#define VARIABLE_H

#include<string>


enum VariableType{
	_INTEGER_,
	_DECIMAL_,
	_STRING_,
	_BOOLEAN_,
	_CUSTOM_
};


class Variable{
	VariableType type;
	std::string name;
	
	public:
		Variable(VariableType type, std::string name){
			this->type = type;
			this->name = name;
		}
		
		VariableType get_type(){
			return this->type;
		}
		
		std::string get_name(){
			return this->name;
		}
};


class DefaultVariable : public Variable{
	std::string value;
	
	public:
		DefaultVariable(VariableType type, std::string name, std::string value) : Variable(type, name){
			this->value = value;
		}
		
		std::string get_value(){
			return this->value;
		}
		
		
};

class CustomVariable : public Variable{
	std::vector<Variable*> value;
	std::string class_name;
	
	public:
		CustomVariable(VariableType type, std::string name, std::string class_name) : Variable(type, name){
			this->class_name = class_name;
		}
		
		void add_member(Variable* member){
			// make sure the member is not already added and such member variable exists in the class
			this->value.push_back(member);
		}
		
		// implement get_value()
	
};

#endif
