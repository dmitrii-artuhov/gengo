#include "../gengo.h"
#include "../headers/token.h"
#include "../headers/parser.h"





Parser::Parser(std::vector <Token> &tokens) :
	tokens(tokens),
	token_index(-1) {
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


ASTNode* Parser::parse() {
	ASTNode* res = this->Expr();
	return res;
}


ASTNode* Parser::Factor() {
	Token token = this->curr_token;
	std::string t = token.type;
	ASTNode* node;

	if (t == TOKEN_PLUS || t == TOKEN_MINUS) {
		this->Advance();
		ASTNode* factor = this->Factor();
		node = new ASTNode(token, factor);
		// this->Advance(); ???
	}
	else if (t == TOKEN_INT || t == TOKEN_FLOAT) {
		node = new ASTNode(token);
		this->Advance();
	}
	else if (t == TOKEN_LPAREN) {
		this->Advance();
		node = this->Expr();

		if (this->curr_token.type == TOKEN_RPAREN) {
			this->Advance();
		}
		else {
			// syntax error
		}
	}

	return node;

}

ASTNode* Parser::Term() {
	ASTNode* left = this->Factor();

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;

		while (t == TOKEN_DIV || t == TOKEN_MULT) {
			Token oper_token = this->curr_token;
			
			this->Advance();
			
			ASTNode* right = this->Factor();

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}
	}
	return left;
}

ASTNode* Parser::Expr() {
	ASTNode* left = this->Term();

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;
		while (t == TOKEN_PLUS || t == TOKEN_MINUS) {
			Token oper_token = this->curr_token;

			this->Advance();

			ASTNode* right = this->Term();

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}
	}
	return left;
}


