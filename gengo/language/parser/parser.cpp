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
	// this->ParseRes = this->Expr();
	this->ParseRes = this->Statements();

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

ParseResult* Parser::Statements() {
	std::vector <ASTNode*> statements;
	ParseResult* res = new ParseResult();

	while (this->curr_token.type != TOKEN_EOF) {
		// This stunt may cause some bad errors in the future, so
		// think about refactor one day
		int idx = this->token_index;
		ASTNode* expr = res->TryRegister(this->Expr());

		if (!expr) {
			this->curr_token = this->tokens[idx];
			this->token_index = idx;
			break;
		}

		if (this->curr_token.type != TOKEN_NEWLINE) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected ';'"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		statements.push_back(expr);
		this->Advance();
	}

	return res->Success(new ASTNode(statements));
}

ParseResult* Parser::Expr() {
	ParseResult* res = new ParseResult();

	// KEYWORD:TYPE INDETIFIER EQ expr
	if (this->curr_token.type == TOKEN_TYPE) {
		Token type_token = this->curr_token;
		this->Advance();

		if (this->curr_token.type != TOKEN_IDENTIFIER) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected identifier"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		std::string var_name = this->curr_token.value;
		this->Advance();

		if (this->curr_token.type != TOKEN_EQ) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '='"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();

		ASTNode* node = res->Register(this->Expr());

		if (res->error) {
			return res;
		}

		return res->Success(new ASTNode(type_token, var_name, node));
	}
	// INDETIFIER EQ expr
	else if (this->curr_token.type == TOKEN_IDENTIFIER && this->tokens[this->token_index + 1].type == TOKEN_EQ) {
		// it is ok to put 'this->token_index + 1' because if current token is an indetifier then after it there will be at least TOKEN_EOF
		// try variable reassignment
		std::string var_name = this->curr_token.value;

		this->Advance();
		this->Advance(); // skip TOKEN_EQ (cuz we have already checked it in the condition)

		ASTNode* node = res->Register(this->Expr());

		if (res->error) {
			return res;
		}

		return res->Success(new ASTNode(var_name, node)); // returns reassign node 
	}
	// comp-expr
	else {
		ASTNode* node = res->Register(this->CompExpr());

		if (res->error) {
			return res;
		}

		return res->Success(node);
	}
}

ParseResult* Parser::CompExpr() {
	ParseResult* res = new ParseResult();

	// register a new ArithExpr
	ASTNode* left = res->Register(this->ArithExpr());

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;
		while ( t == TOKEN_AND   ||
			    t == TOKEN_OR    ||
			    t == TOKEN_EQEQ  ||
				t == TOKEN_NE	 ||
				t == TOKEN_GT    ||
				t == TOKEN_GTE   ||
				t == TOKEN_LT    ||
				t == TOKEN_LTE
			) {
			Token oper_token = this->curr_token;

			this->Advance();

			ASTNode* right = res->Register(this->ArithExpr());

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}


		return res->Success(left);
	}

	return res->Failure(new Error(
		ERROR_INVALID_SYNTAX,
		std::string("Expected identifier or expression"),
		this->curr_token.pos_start,
		this->curr_token.pos_end
	));
}

ParseResult* Parser::ArithExpr() {
	ParseResult* res = new ParseResult();

	// register a new Term
	ASTNode* left = res->Register(this->Term());

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;
		while (t == TOKEN_PLUS || t == TOKEN_MINUS) {
			Token oper_token = this->curr_token;

			this->Advance();

			ASTNode* right = res->Register(this->Term());

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}


		return res->Success(left);
	}

	return res->Failure(new Error(
		ERROR_INVALID_SYNTAX,
		std::string("Expected identifier or expression"),
		this->curr_token.pos_start,
		this->curr_token.pos_end
	));
}

ParseResult* Parser::Term() {
	ParseResult* res = new ParseResult();

	ASTNode* left = res->Register(this->Factor());

	if (this->curr_token.type != TOKEN_UNDEFINED) {
		std::string t = this->curr_token.type;

		while (t == TOKEN_DIV || t == TOKEN_MULT) {
			Token oper_token = this->curr_token;

			this->Advance();

			ASTNode* right = res->Register(this->Factor());

			if (res->error) {
				return res;
			}

			left = new ASTNode(left, oper_token, right);
			t = this->curr_token.type;
		}


		return res->Success(left);
	}

	return res->Failure(new Error(
		ERROR_INVALID_SYNTAX,
		std::string("Expected '*', '/', '(' or INT|FLOAT"),
		this->curr_token.pos_start,
		this->curr_token.pos_end
	));
}

ParseResult* Parser::Factor() {
	ParseResult* res = new ParseResult();
	ASTNode* node;

	if (this->curr_token.type == TOKEN_PLUS || this->curr_token.type == TOKEN_MINUS) {
		Token token = this->curr_token;

		this->Advance();
		ASTNode* factor = res->Register(this->Factor());
		node = new ASTNode(token, factor);
		// this->Advance(); ???

		return res->Success(node);
	}
	else if (this->curr_token.type == TOKEN_IDENTIFIER || this->curr_token.type == TOKEN_INT || this->curr_token.type == TOKEN_FLOAT) {
		node = new ASTNode(this->curr_token);
		this->Advance();

		return res->Success(node);
	}
	else if (this->curr_token.type == TOKEN_KEYWORD && this->curr_token.value == KEYWORD_IF) {
		ASTNode* ifExpr = res->Register(this->IfExpr());
		if (res->error)
			return res;
		else
			return res->Success(ifExpr);
	}
	else if (this->curr_token.type == TOKEN_LPAREN) {
		this->Advance();
		node = res->Register(this->Expr());

		if (res->error) {
			return res;
		}

		if (this->curr_token.type == TOKEN_RPAREN) {
			this->Advance();
			return res->Success(node);
		}
		else {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected ')'"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}
	}
	else if (this->curr_token.type == TOKEN_NOT) {
		Token token = this->curr_token;

		this->Advance();
		node = res->Register(this->CompExpr());

		if (res->error) {
			return res;
		}
				
		return res->Success(new ASTNode(token, node)); // add unary not-operator
	}

	return res->Failure(new Error(
		ERROR_INVALID_SYNTAX,
		std::string("Expected '+', '-', '(' or INT|FLOAT|IDENTIFIER"),
		this->curr_token.pos_start,
		this->curr_token.pos_end
	));
}


ParseResult* Parser::IfExpr() {
	ParseResult* res = new ParseResult();
	std::vector <std::pair <ASTNode*, ASTNode*>> cases;
	ASTNode* else_case = nullptr;

	// first if 
	if (this->curr_token.value != KEYWORD_IF) {
		return res->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected '" + KEYWORD_IF + "'"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	this->Advance();

	if (this->curr_token.type != TOKEN_LPAREN) {
		return res->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected '(' before condition"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	this->Advance();

	ASTNode* condition = res->Register(this->Expr());

	if (res->error)
		return res;

	if (this->curr_token.type != TOKEN_RPAREN) {
		return res->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected ')' after condition"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	this->Advance();

	if (this->curr_token.type != TOKEN_LBRACE) {
		return res->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected '{' before condition body"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	this->Advance();
	ASTNode* statements = res->Register(this->Statements());

	if (res->error)
		return res;

	if (this->curr_token.type != TOKEN_RBRACE) {
		return res->Failure(new Error(
			ERROR_INVALID_SYNTAX,
			std::string("Expected '}' after condition body"),
			this->curr_token.pos_start,
			this->curr_token.pos_end
		));
	}

	this->Advance();

	cases.push_back({ condition, statements });

	// look for else-if's

	while (this->curr_token.value == KEYWORD_ELIF) {
		this->Advance();

		if (this->curr_token.type != TOKEN_LPAREN) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '(' before condition"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();

		condition = res->Register(this->Expr());

		if (res->error)
			return res;

		if (this->curr_token.type != TOKEN_RPAREN) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected ')' after condition"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();

		if (this->curr_token.type != TOKEN_LBRACE) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '{' before condition body"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();
		statements = res->Register(this->Statements());

		if (res->error)
			return res;

		if (this->curr_token.type != TOKEN_RBRACE) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '}' after condition body"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();

		cases.push_back({ condition, statements });
	}

	if (this->curr_token.value == KEYWORD_ELSE) {
		this->Advance();

		if (this->curr_token.type != TOKEN_LBRACE) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '{' before condition body"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();

		else_case = res->Register(this->Statements());

		if (res->error)
			return res;


		if (this->curr_token.type != TOKEN_RBRACE) {
			return res->Failure(new Error(
				ERROR_INVALID_SYNTAX,
				std::string("Expected '}' after condition body"),
				this->curr_token.pos_start,
				this->curr_token.pos_end
			));
		}

		this->Advance();
	}

	return res->Success(new ASTNode(cases, else_case));
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

ASTNode* ParseResult::TryRegister(ParseResult* res) {
	if (res->error) return nullptr;
	else return this->Register(res);
}