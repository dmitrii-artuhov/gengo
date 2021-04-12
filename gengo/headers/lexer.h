#pragma once

#include "./position.h"
#include "./error.h"

class Lexer {
private:
	std::string text, file_name;
	Position *pos;
	char curr_char;

	bool hasError;
	IllegalCharError* err;

public:
	Lexer(std::string& file_name, std::string& text);

	void Advance();
	Token MakeNumber();
	
	std::vector <Token> MakeTokens();
	
	// getters
	std::pair<bool, IllegalCharError*> getError();
};


