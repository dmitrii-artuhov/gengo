/*--- Tokens -----------------------*/
#include "../gengo.h"
#include "../headers/token.h"


Token::Token() :
	type(TOKEN_UNDEFINED), value("") {}

Token::Token(const std::string& type, std::string value) :
	type(type), value(value) {}

std::string Token::Represent() {
	std::string output = "";

	if (this->value != "") {
		output = this->type + ":" + this->value;
	}
	else {
		output = this->type;
	}

	return output;
}

Token* Token::Copy() {
	const std::string type = this->type;
	std::string val = this->value;

	return new Token(type, val);
}