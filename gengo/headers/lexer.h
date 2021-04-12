#pragma once

#include "../headers/error.h"

class Lexer {
private:
	std::string text;
	int pos;
	char curr_char;

	bool hasError;
	IllegalCharError* err;

public:
	Lexer(std::string& text);

	void Advance();
	Token MakeNumber();
	
	std::vector <Token> MakeTokens();
	
	// getters
	std::pair<bool, IllegalCharError*> getError();
};


