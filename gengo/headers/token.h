#pragma once


class Token {
private:
	std::string type;
	std::string value;

public:
	Token(const std::string &type, std::string value = "");
	std::string Represent();
};


