/*--- Tokens -----------------------*/
#include "../../gengo.h"
#include "./token.h"


Token::Token() :
	type(TOKEN_UNDEFINED),
	value(""),
	pos_start(Position(0, 0, 0, std::string("<undefined>"), std::string("<undefined>"))),
	pos_end(Position(0, 0, 0, std::string("<undefined>"), std::string("<undefined>"))) {}

Token::Token(const std::string& type, Position& pos_start, Position& pos_end, std::string value) :
	type(type), value(value), pos_start(pos_start), pos_end(pos_end) {}

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
	return new Token(this->type, this->pos_start, this->pos_end, this->value);
}