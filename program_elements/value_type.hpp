#ifndef VALUE_TYPE_H
#define VALUE_TYPE_H


enum ValueType{
	_VOID_,
	_INTEGER_,
	_DECIMAL_,
	_STRING_,
	_BOOLEAN_,
	_CUSTOM_
};

//
//class ValueHolder{
//	ValueType type;
//	
//	public:
//		
//		ValueHolder(ValueType type){
//			this->type = type;
//		}
//		
//		ValueType get_type(){
//			return this->type;
//		}
//		
//		virtual std::string get_value() = 0;
//};
//
//
//
//class Constant : public ValueHolder{
//	std::string value;
//	
//	public:
//		Constant(ValueType type, std::string value) : ValueHolder(type){
//			this->value = value;
//		}
//		
//		std::string get_value(){
//			return this->value;
//		}
//	
//};
//
//
//
//class Variable : public ValueHolder{
//	std::string name;
//	
//	public:
//		Variable(ValueType type, std::string name) : ValueHolder(type){
//			this->name = name;
//		}
//		
//		std::string get_name(){
//			return this->name;
//		}
//		
//};
//
//
//
//
//class DefaultVariable : public Variable{
//	std::string value;
//	
//	public:
//		DefaultVariable(ValueType type, std::string name, std::string value) : Variable(type, name){
//			this->value = value;
//		}
//		
//		std::string get_value(){
//			return this->value;
//		}
//		
//		void set_value(std::string value){
//			this->value = value;
//		}
//};

//class CustomVariable : public Variable{
//	std::vector<Variable*> value;
//	std::string class_name;
//	
//	public:
//		CustomVariable(VariableType type, std::string name, std::string class_name) : Variable(type, name){
//			this->class_name = class_name;
//		}
//		
//		void add_member(Variable* member){
//			// make sure the member is not already added and such member variable exists in the class
//			this->value.push_back(member);
//		}
//		
//		// implement get_value()
//	
//};

#endif
