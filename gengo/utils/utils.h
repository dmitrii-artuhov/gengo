#pragma once

#include <unordered_map>

// string -> long long
long long cast_string_to_ll(std::string& s);

long double cast_string_to_ld(std::string& s);

// concatinate strings
std::string cancat(std::vector <std::string>& arr);

// print vector
template <typename T>
void print_vector(std::vector <T> &arr, std::string &sep);