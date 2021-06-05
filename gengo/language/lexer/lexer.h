#pragma once


#include "../tokens/token.h"
#include "../tokens/position.h"
#include "../error/error.h"




class LexerResult;

class Lexer {
private:
	std::string text, file_name;
	Position pos;
	char curr_char;

	//bool hasError;
	//Error* err;
	LexerResult* LexResult;

public:
	Lexer(std::string& file_name, std::string& text);
	void Advance();

	// Helpers
	Token MakeIdentifier(); // typedefine | variable | and | or | not
	Token MakeNumberToken();
	Token MakeStringToken();
	Token MakeEquals(); // '=' | '=='
	Token MakeGreaterEquals(); // '>' | '>='
	Token MakeLessEquals(); // '<' | '<='

	
	LexerResult* MakeTokens();
};


class LexerResult {
private:
public:
	std::vector <Token> tokens;
	Error* error;

	LexerResult();
	LexerResult(std::vector <Token> tokens, Error* err);
};


