#include<iostream>
#include<string>
#include<vector>
#include<regex>

std::vector<std::string> rex_split(const std::string &s, const std::string& rgx_str = "\\s+"){
	std::vector<std::string> elems;
	std::basic_regex<char> rgx (rgx_str);
	
	std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
	std::sregex_token_iterator end;
	
	while(iter != end){
		if ((*iter).length() > 0)
			elems.push_back(*iter);
		++iter;
	}
	
	return elems;
}

int main(){
	std::string s = "   this is some (#$%^)random string"
	"\t  with\tsome\nspaces    .     ";
	std::vector<std::string> result = rex_split(s);
	
	
	
	for(std::string x: result){
		std::cout << "\"" << x << "\"" << std::endl;
	}
	std::cout << "---------";
}

