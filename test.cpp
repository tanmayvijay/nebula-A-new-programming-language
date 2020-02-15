#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include "var_type.hpp"
using namespace std;

int main(){
	
	std::string type_ = "integer";
	std::transform(type_.begin(), type_.end(), type_.begin(), ::toupper);
//	cout << type_;

	std::map<std::string, VAR_TYPE> var_type_mapping {
				{"STRING", STRING_},
				{"INTEGER", INTEGER_},
				{"BOOLEAN", BOOLEAN_},
				{"DECIMAL", DECIMAL_}
			};

	cout << var_type_mapping.find(type_)->second;
	
	
	return 0;
}
