#include<iostream>
#include<string>
#include<vector>
#include<regex>

#include "../tokenizer/tokenizer.hpp"
#include "../utils/utils.hpp"
using namespace std;
int main(){
	
	string x = "  	som_e _ { th+e-df{}+-*bkjd {ajbfkjdfa} }{82{7468 + {} \"some-thing\n\nj)hf\\\"nd \n (kjdfjkd) (  ) sj(fbgjdkg\n +  - *  / ^ \ngr e8757858-587)-587a 868 t here\"  hfd875 87 jf af + -  \"here's another string'\"		 *    / % ^   235-2837547382-48.18)(5748713 (akdbfkjd) (   ) adjf(hvjh			sdjb)k	 kjdbfk	kjbsdk	skvj   \t\t adsk -82734 jsbfkjjhdvsdjhb";
	Tokenizer tok;
	
	std::vector<Token> tokens = tok.tokenize(x);
	for (Token t: tokens){
		cout << t.get_token_type() << " - " << t.get_token_data() << endl;
	}
}
