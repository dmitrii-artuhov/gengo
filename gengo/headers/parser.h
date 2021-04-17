#pragma once
#include "../gengo.h"
#include "./token.h"
#include "./ast.h"





class Parser {
private:
	std::vector <Token> tokens;
	int token_index;
	Token curr_token;

public:
	Parser(std::vector <Token> &tokens);
	void Advance();

	ASTNode* parse();

	ASTNode* Factor();
	ASTNode* Term();
	ASTNode* Expr();
};












