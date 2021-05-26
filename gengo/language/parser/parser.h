#pragma once
#include "../../gengo.h"
#include "../tokens/token.h"
#include "../nodes/ast.h"
#include "../error/error.h"


class ParseResult;

/*--- Parser -----------------------------------------*/
class Parser {
private:
	std::vector <Token> tokens;
	int token_index;
	Token curr_token;
	ParseResult* ParseRes;

public:
	Parser(std::vector <Token> &tokens);
	void Advance();

	ParseResult* parse();

	ParseResult* Statements();
	ParseResult* Expr();
	ParseResult* CompExpr();
	ParseResult* ArithExpr();
	ParseResult* Term();
	ParseResult* Factor();
	ParseResult* IfExpr();
	ParseResult* ForExpr();
	ParseResult* FuncDeclExpr();
};


/*--- ParseResult -----------------------------------------*/
class ParseResult {
private:
public:
	ASTNode* ast;
	Error* error;

	ParseResult();
	ParseResult(ASTNode* ast, Error* err);

	ParseResult* Failure(Error* err);
	ParseResult* Success(ASTNode* ast);
	ASTNode* Register(ParseResult* res);
	ASTNode* TryRegister(ParseResult* res);
};











