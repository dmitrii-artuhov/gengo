/*--- Lexer -----------------------*/
// the order of includes matter

#include "../gengo.h"
#include "../utils/cast_types.h"
#include "../headers/globals.h"

#include "../headers/token.h"

#include "../headers/position.h"
#include "../headers/error.h" // goes before lexer
#include "../headers/lexer.h"



Lexer::Lexer(std::string& file_name, std::string& text) :
	text(text),
	file_name(file_name),
	pos(new Position(-1, 0, -1, file_name, text)),
	curr_char(NULL),
	hasError(false),
	err(NULL)
{
	this->Advance();
}

void Lexer::Advance() {
	this->pos->Advance(this->curr_char);
	this->curr_char = (this->pos->index < text.size()) ? this->text[this->pos->index] : NULL;
}

Token Lexer::MakeNumber() {
	std::string num_str = "";
	int dot_cnt = 0;
	std::string collection = DIGITS + ".";

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
		return Token(TOKEN_INT, num_str);
	}
	else {
		return Token(TOKEN_FLOAT, num_str);
	}
}

std::vector <Token> Lexer::MakeTokens() {
	std::vector <Token> tokens;

	while (this->curr_char != NULL) {
		if (this->curr_char == ' ' || this->curr_char == '\t') {
			this->Advance();
		}
		else if (DIGITS.find(this->curr_char) != std::string::npos) {
			tokens.push_back(this->MakeNumber());
		}
		else if (this->curr_char == '+') {
			tokens.push_back(Token(TOKEN_PLUS));
			this->Advance();
		}
		else if (this->curr_char == '-') {
			tokens.push_back(Token(TOKEN_MINUS));
			this->Advance();
		}
		else if (this->curr_char == '*') {
			tokens.push_back(Token(TOKEN_MULT));
			this->Advance();
		}
		else if (this->curr_char == '/') {
			tokens.push_back(Token(TOKEN_DIV));
			this->Advance();
		}

		else if (this->curr_char == '(') {
			tokens.push_back(Token(TOKEN_LPAREN));
			this->Advance();
		}
		else if (this->curr_char == ')') {
			tokens.push_back(Token(TOKEN_RPAREN));
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
			
			Position* pos_start = this->pos->Copy();
			this->Advance();

			this->hasError = true;
			this->err = new IllegalCharError(details, pos_start, this->pos);

			return tokens;
		}
	}

	return tokens;
}


// getters
std::pair<bool, IllegalCharError*> Lexer::getError() {
	return std::make_pair(
		this->hasError,
		this->err
	);
}