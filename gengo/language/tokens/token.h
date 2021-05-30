#pragma once

#include "./position.h"

/*--- Tokens ----------------------------------------*/
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

TOKEN_LBRACE = "LBRACE", // {
TOKEN_RBRACE = "RBRACE", // }

TOKEN_EQ = "EQ",
TOKEN_EQEQ = "EQEQ", // ==
TOKEN_NE = "NE", // !=
TOKEN_GT = "GT", // >
TOKEN_GTE = "GTE", // >=
TOKEN_LT = "LT", // <
TOKEN_LTE = "LTE", // <=

TOKEN_NEWLINE = "NEWLINE", // ;
TOKEN_COLON = "COLON", // :
TOKEN_ARROW = "ARROW", // ->
TOKEN_COMMA = "COMMA", // ,
TOKEN_EOF = "EOF",

TOKEN_TYPE = "TYPE",
TOKEN_KEYWORD = "KEYWORD",
TOKEN_IDENTIFIER = "IDENTIFIER";


/*--- Helpers -----------------------------------------------*/
const std::string
DIGITS = "0123456789",
LETTERS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


/*--- Language requirements ----------------------------------------------------------*/
const std::string
	TYPE_INT = "int",
	TYPE_FLOAT = "float";

const std::string
	KEYWORD_AND = "and",
	KEYWORD_OR = "or",
	KEYWORD_NOT = "not",

	KEYWORD_IF = "if",
	KEYWORD_ELIF = "elif",
	KEYWORD_ELSE = "otherwise",
	KEYWORD_FOR = "loop", // loop(initialization; condition; incrementation) {  };
	KEYWORD_FUNCTION = "function",
	KEYWORD_RETURN = "return";


const std::vector <std::string> TYPES = {
	TYPE_INT,
	TYPE_FLOAT
};

const std::vector <std::string> KEYWORDS = {
	KEYWORD_IF,
	KEYWORD_ELIF,
	KEYWORD_ELSE,
	KEYWORD_FOR,
	KEYWORD_FUNCTION,
	KEYWORD_RETURN
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


