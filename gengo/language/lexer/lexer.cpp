/*--- Lexer -----------------------*/
// the order of includes matter

#include "../../gengo.h"
#include "../../utils/utils.h"

#include "../tokens/token.h"

#include "../tokens/position.h"
#include "../error/error.h" // goes before lexer
#include "../lexer/lexer.h"



/*--- Lexer ------------------------------------------------*/
Lexer::Lexer(std::string& file_name, std::string& text) :
	text(text),
	file_name(file_name),
	pos(Position(-1, 0, -1, file_name, text)),
	curr_char(NULL),
	LexResult(NULL)
{
	this->Advance();
}

void Lexer::Advance() {
	this->pos.Advance(this->curr_char);
	this->curr_char = (this->pos.index < text.size()) ? this->text[this->pos.index] : NULL;
}

Token Lexer::MakeNumberToken() {
	std::string num_str = "";
	int dot_cnt = 0;
	std::string collection = DIGITS + ".";

	Position pos_start = this->pos.Copy();

	while (this->curr_char != NULL
		&& collection.find(this->curr_char) != std::string::npos) {
		if (this->curr_char == '.') {
			if (dot_cnt != 0) break;
			dot_cnt++;
		}

		num_str += this->curr_char;
		this->Advance();
	}

	if (dot_cnt == 0) {
		return Token(TOKEN_INT, pos_start, this->pos, num_str);
	}
	else {
		return Token(TOKEN_FLOAT, pos_start, this->pos, num_str);
	}
}

Token Lexer::MakeIdentifier() {
	std::string id_str = "";
	std::string collection = DIGITS + LETTERS + "_";
	
	Position pos_start = this->pos.Copy();

	while (this->curr_char != NULL
		&& collection.find(this->curr_char) != std::string::npos) {
		id_str += this->curr_char;
		this->Advance();
	}
	
	if (find(TYPES.begin(), TYPES.end(), id_str) != TYPES.end()) {
		return Token(TOKEN_TYPE, pos_start, this->pos, id_str);
	}
	else if (find(KEYWORDS.begin(), KEYWORDS.end(), id_str) != KEYWORDS.end()) {
		return Token(TOKEN_KEYWORD, pos_start, this->pos, id_str);
	}
	else {
		return Token(TOKEN_IDENTIFIER, pos_start, this->pos, id_str);
	}
}

LexerResult* Lexer::MakeTokens() {
	std::vector <Token> tokens;

	while (this->curr_char != NULL) {
		if (this->curr_char == ' ' || this->curr_char == '\t') {
			this->Advance();
		}
		else if (DIGITS.find(this->curr_char) != std::string::npos) {
			tokens.push_back(this->MakeNumberToken());
		}
		else if (this->curr_char == '+') {
			tokens.push_back(Token(TOKEN_PLUS, this->pos, this->pos));
			this->Advance();
		}
		else if (this->curr_char == '-') {
			tokens.push_back(Token(TOKEN_MINUS, this->pos, this->pos));
			this->Advance();
		}
		else if (this->curr_char == '*') {
			tokens.push_back(Token(TOKEN_MULT, this->pos, this->pos));
			this->Advance();
		}
		else if (this->curr_char == '/') {
			tokens.push_back(Token(TOKEN_DIV, this->pos, this->pos));
			this->Advance();
		}
		else if (this->curr_char == '(') {
			tokens.push_back(Token(TOKEN_LPAREN, this->pos, this->pos));
			this->Advance();
		}
		else if (this->curr_char == ')') {
			tokens.push_back(Token(TOKEN_RPAREN, this->pos, this->pos));
			this->Advance();
		}
		else if (std::string("_" + LETTERS).find(this->curr_char) != std::string::npos) {
			tokens.push_back(this->MakeIdentifier());
		}
		else if (this->curr_char == '=') {
			// upgrade to find ==
			tokens.push_back(Token(TOKEN_EQ, this->pos, this->pos));
			this->Advance();
		}
		else {
			tokens.clear();

			std::string details = "";
			{
				details += '\'';
				details += this->curr_char;
				details += '\'';
			}
			
			Position pos_start = this->pos.Copy();
			this->Advance();

			this->LexResult = new LexerResult(
				tokens,
				new Error(ERROR_ILLEGAL_CHAR, details, pos_start, this->pos)
			);

			return this->LexResult;
		}
	}

	Token eof = Token(TOKEN_EOF, this->pos, this->pos);
	tokens.push_back(eof);

	this->LexResult = new LexerResult(
		tokens,
		NULL
	);

	// DEBUG
	if (GENGO_DEBUG)
		for (Token t : tokens) {
			std::cout << t.Represent() << std::endl;
		}

	return this->LexResult;
}







/*--- LexerResult ----------------------------------------------*/
LexerResult::LexerResult() {
	this->error = nullptr;
	this->tokens = {};
}

LexerResult::LexerResult(std::vector <Token> tokens, Error* err):
tokens(tokens), error(err) {}
