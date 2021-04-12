/*--- Run - read text input ----------------------*/

#include "../gengo.h"
#include "../headers/run.h"
#include "../headers/token.h"
#include "../headers/lexer.h"
#include "../headers/error.h"



std::pair<
	std::vector<Token>,
	IllegalCharError*
> run(std::string& file_name, std::string& text) {
	Lexer lexer(file_name, text);
	std::vector <Token> tokens = lexer.MakeTokens();

	std::pair<std::vector <Token>, IllegalCharError*> res = {
		tokens,
		NULL
	};

	std::pair<bool, IllegalCharError*> error = lexer.getError();
	if (error.first) {
		res.second = error.second;
	}

	return res;
}