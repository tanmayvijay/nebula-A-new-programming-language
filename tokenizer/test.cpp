#include<iostream>
#include<string>

#include "tokenizer.hpp"

using namespace std;
int main(){
	string s ="type var_name = \"value\"\n"
				"int x = 234\n"
				"print \"Hello World!\"\n";
		
	tokenizer tz(s);

	while(tz.has_next_token()){
		cout << tz.next_token().get_token() << endl;
	}
	
}
