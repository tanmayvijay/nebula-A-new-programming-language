#include<iostream>
#include<string>
#include<vector>
#include<regex>

#include "../tokenizer/tokenizer.hpp"
#include "../utils/utils.hpp"
using namespace std;
int main(){
	
	string x = "  	som_e _ th+e-df+-*bkjd 827468 + \"some-thing\n\njhf\\\"nd \n sjfbgjdkg\n +  - *  / ^ \ngr e8757858-587 -587a 868 t here\"  hfd875 87 jf af + -  \"here's another string'\"		 *    / % ^   235-2837547382-48.185748713 adjfhvjh			sdjbk	 kjdbfk	kjbsdk	skvj   \t\t adsk -82734 jsbfkjjhdvsdjhb";
	Tokenizer tok;
	
	std::vector<Token> tokens = tok.tokenize(x);
//	for (Token t: tokens){
//		cout << t.get_token_type() << " - " << t.get_token_data() << endl;
//	}
}
