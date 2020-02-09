#include<iostream>
#include<string>

#include "tokenizer.hpp"

using namespace std;
int main(){
	string s ="type var_name = \"value\"\n";
		s += "int x = 234\n";
		s += "print \"Hello World!\"\n";
		
	tokenizer tz(s);

	while(tz.has_next_token()){
		cout << tz.next_token().get_token();
	}
	
}
