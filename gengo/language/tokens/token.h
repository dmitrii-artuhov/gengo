#pragma once

#include "./position.h"

const std::string
TOKEN_UNDEFINED = "UNDEFINED",
TOKEN_INT = "INT",
TOKEN_FLOAT = "FLOAT",
TOKEN_PLUS = "PLUS",
TOKEN_MINUS = "MINUS",
TOKEN_MULT = "MULT",
TOKEN_DIV = "DIV",
TOKEN_LPAREN = "LPAREN",
TOKEN_RPAREN = "RPAREN",
TOKEN_EOF = "EOF";


const std::string
DIGITS = "0123456789";


class Token {
private:

public:
	std::string type;
	std::string value;
	Position pos_start, pos_end;

	Token();
	Token(const std::string &type, Position& pos_start, Position& pos_end, std::string value = "");
	std::string Represent();
	Token* Copy();
};


