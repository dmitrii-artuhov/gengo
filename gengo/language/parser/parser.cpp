#include "../../gengo.h"
#include "../tokens/token.h"
#include "../parser/parser.h"
#include "../error/error.h"



/*--- Parser -----------------------------------------*/
Parser::Parser(std::vector <Token> &tokens) :
	tokens(tokens),
	token_index(-1),
	ParseRes(new ParseResult()) {
	this->Advance();
}


void Parser::Advance() {
	this->token_index++;

	if (this->token_index < this->tokens.size()) {
		this->curr_token = this->tokens[token_index];
	}
	else {
		Token t;
		this->curr_token = t;
	}
}


ParseResult* Parser::parse() {
	this->ParseRes = this->Expr();

	if (!this->ParseRes->error && this->curr_token.type != TOKEN_EOF) {
		std::string details = "Expected '+', '-', '*' or '/'";

		return this->ParseRes->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			details,
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	return this->ParseRes;
}


ParseResult* Parser::Factor() {
	ASTNode* node;

	if (this->curr_token.type == TOKEN_PLUS || this->curr_token.type == TOKEN_MINUS) {
		this->Advance();
		ASTNode* factor = this->ParseRes->Register(this->Factor());
		node = new ASTNode(this->curr_token, factor);
		// this->Advance(); ???
	}
	else if (this->curr_token.type == TOKEN_INT || this->curr_token.type == TOKEN_FLOAT) {
		node = new ASTNode(this->curr_token);
		this->Advance();
	}
	else if (this->curr_token.type == TOKEN_LPAREN) {
		this->Advance();
		node = this->ParseRes->Register(this->Expr());

		if (this->curr_token.type == TOKEN_RPAREN) {
			this->Advance();
		}
		else {
			std::string details = "Expected ')'";
			return this->ParseRes->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				details,
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}
	}

	return this->ParseRes->Success(node);
}

ParseResult* Parser::Term() {
	ASTNode* left = this->ParseRes->Register(this->Factor());

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;

		while (t == TOKEN_DIV || t == TOKEN_MULT) {
			Token oper_token = this->curr_token;
			
			this->Advance();
			
			ASTNode* right = this->ParseRes->Register(this->Factor());

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}
	}
	return this->ParseRes->Success(left);
}

ParseResult* Parser::Expr() {
	ASTNode* left = this->ParseRes->Register(this->Term());

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;
		while (t == TOKEN_PLUS || t == TOKEN_MINUS) {
			Token oper_token = this->curr_token;

			this->Advance();

			ASTNode* right = this->ParseRes->Register(this->Term());

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}
	}
	return this->ParseRes->Success(left);
}



/*--- ParseResult -----------------------------------------*/
ParseResult::ParseResult():
ast(nullptr), error(nullptr) {}

ParseResult::ParseResult(ASTNode* ast, Error* err):
ast(ast), error(err) {}


ParseResult* ParseResult::Failure(Error* err) {
	this->error = err;
	return this;
}

ParseResult* ParseResult::Success(ASTNode* ast) {
	this->ast = ast;
	return this;
}

ASTNode* ParseResult::Register(ParseResult* res) {
	if (res->error) {
		this->error = res->error;
	}
	return res->ast;
}