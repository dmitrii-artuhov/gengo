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

TOKEN_AND = "AND",
TOKEN_OR = "OR",
TOKEN_NOT = "NOT",

TOKEN_LPAREN = "LPAREN",
TOKEN_RPAREN = "RPAREN",

TOKEN_EQ = "EQ",
TOKEN_EQEQ = "EQEQ", // ==
TOKEN_GT = "GT", // >
TOKEN_GTE = "GTE", // >=
TOKEN_LT = "LT", // <
TOKEN_LTE = "LTE", // <=

TOKEN_EOF = "EOF",

TOKEN_TYPE = "TYPE",
TOKEN_KEYWORD = "KEYWORD",
TOKEN_IDENTIFIER = "IDENTIFIER"
;


const std::string
DIGITS = "0123456789",
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


const std::vector <std::string> TYPES = {
	"int",
	"float"
};

const std::vector <std::string> KEYWORDS = {

};


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


