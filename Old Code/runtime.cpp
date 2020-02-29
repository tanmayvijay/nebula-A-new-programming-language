#include<iostream>
#include<string>
#include<vector>

//#include "block/block.hpp"
//#include "block/class_block.hpp"
#include "tokenizer/tokenizer.hpp"
//#include "parser/parser.hpp"
//#include "parser/class_parser.hpp"
//#include "parser/function_parser.hpp"
//#include "parser/parser.hpp"

using namespace std;

int main(){
	
//	vector<CLASS_BLOCK> classes;
	
	string code = "display , .   = \"Hello World, Nebula here! \"\n"
					"string x = \"Hello\"\n"
					"display x\n";
//					cout << code;
	
	TOKENIZER tokenizer = TOKENIZER(code);
	
	while(tokenizer.has_next_token()){
		cout << tokenizer.next_token().get_token() << endl;
	}
//	vector<PARSER*> parsers;
//	parsers.push_back(new CLASS_PARSER())
					
	return 0;
}
