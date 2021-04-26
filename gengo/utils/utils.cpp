#include "../gengo.h"
#include "./utils.h"

long long cast_string_to_ll(std::string& s) {
	return std::stoll(s);
}

long double cast_string_to_ld(std::string& s) {
	return std::stold(s);
}


std::string cancat(std::vector <std::string>& arr) {
	std::string res = "";

	for (std::string& s : arr) res += s;
	
	return res;
}

template <typename T>
void print_vector(std::vector <T>& arr, std::string &sep) {
	for (T a : arr) {
		std::cout << a << sep;
	}
}

