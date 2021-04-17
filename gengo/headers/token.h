#pragma once

const std::string
TOKEN_UNDEFINED = "UNDEFINED",
TOKEN_INT = "INT",
TOKEN_FLOAT = "FLOAT",
TOKEN_PLUS = "PLUS",
TOKEN_MINUS = "MINUS",
TOKEN_MULT = "MULT",
TOKEN_DIV = "DIV",
TOKEN_LPAREN = "LPAREN",
TOKEN_RPAREN = "RPAREN";


const std::string
DIGITS = "0123456789";


class Token {
private:

public:
	std::string type;
	std::string value;

	Token();
	Token(const std::string &type, std::string value = "");
	std::string Represent();
	Token* Copy();
};


