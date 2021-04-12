#include "../gengo.h"



long long cast_string_to_ll(std::string& s) {
	long long res = 0;

	for (int i = 0; i < s.size(); i++) {
		res *= 10;
		res += s[i] - '0';
	}

	return res;
}


std::string cancat(std::vector <std::string>& arr) {
	std::string res = "";

	for (std::string& s : arr) res += s;
	
	return res;
}