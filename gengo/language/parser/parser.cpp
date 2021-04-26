#include "../../gengo.h"
#include "../tokens/token.h"
#include "../parser/parser.h"
#include "../error/error.h"
#include "../nodes/ast.h"



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
		return this->ParseRes->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected '+', '-', '*' or '/'"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	return this->ParseRes;
}


ParseResult* Parser::Factor() {
	ASTNode* node;

	if (this->curr_token.type == TOKEN_PLUS || this->curr_token.type == TOKEN_MINUS) {
		Token token = this->curr_token;

		this->Advance();
		ASTNode* factor = this->ParseRes->Register(this->Factor());
		node = new ASTNode(token, factor);
		// this->Advance(); ???

		return this->ParseRes->Success(node);
	}
	else if (this->curr_token.type == TOKEN_IDENTIFIER || this->curr_token.type == TOKEN_INT || this->curr_token.type == TOKEN_FLOAT) {
		node = new ASTNode(this->curr_token);
		this->Advance();

		return this->ParseRes->Success(node);
	}
	else if (this->curr_token.type == TOKEN_LPAREN) {
		this->Advance();
		node = this->ParseRes->Register(this->Expr());

		if (this->ParseRes->error) {
			return this->ParseRes;
		}

		if (this->curr_token.type == TOKEN_RPAREN) {
			this->Advance();
			return this->ParseRes->Success(node);
		}
		else {
			return this->ParseRes->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected ')'"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}
	}

	return this->ParseRes->Failure(new Error(
		ERROR_INVALID_SYNTAX,
		std::string("Expected '+', '-', '(' or INT|FLOAT"),
		this->curr_token.pos_start,
		this->curr_token.pos_end
	));
}

ParseResult* Parser::Term() {
	ASTNode* left = this->ParseRes->Register(this->Factor());

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;

		while (t == TOKEN_DIV || t == TOKEN_MULT) {
			Token oper_token = this->curr_token;

			this->Advance();

			ASTNode* right = this->ParseRes->Register(this->Factor());

			if (this->ParseRes->error) {
				return this->ParseRes;
			}

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}


		return this->ParseRes->Success(left);
	}

	return this->ParseRes->Failure(new Error(
		ERROR_INVALID_SYNTAX,
		std::string("Expected '*', '/', '(' or INT|FLOAT"),
		this->curr_token.pos_start,
		this->curr_token.pos_end
	));
}

ParseResult* Parser::Expr() {
	if (this->curr_token.type == TOKEN_TYPE) {
		Token type_token = this->curr_token;
		this->Advance();

		if (this->curr_token.type != TOKEN_IDENTIFIER) {
			return this->ParseRes->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected identifier"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}
		
		std::string var_name = this->curr_token.value;
		this->Advance();

		if (this->curr_token.type != TOKEN_EQ) {
			return this->ParseRes->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '='"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();

		ASTNode* node = this->ParseRes->Register(this->Expr());

		if (this->ParseRes->error) {
			return this->ParseRes;
		}

		return this->ParseRes->Success(new ASTNode(type_token, var_name, node));
	}
	else {
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


			return this->ParseRes->Success(left);
		}

		return this->ParseRes->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected identifier or expression"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}
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