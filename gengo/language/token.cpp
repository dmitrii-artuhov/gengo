/*--- Tokens -----------------------*/
#include "../gengo.h"
#include "../headers/token.h"
#include "../headers/globals.h"


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

