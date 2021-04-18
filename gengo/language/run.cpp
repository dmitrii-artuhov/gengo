/*--- Run - read text input ----------------------*/

#include "../gengo.h"
#include "../headers/run.h"
#include "../headers/token.h"
#include "../headers/lexer.h"
#include "../headers/error.h"
#include "../headers/parser.h"
#include "../headers/interpreter.h"


/*
std::pair<
	std::vector<Token>,
	IllegalCharError*
>*/ 
void run(std::string& file_name, std::string& text) {
	Lexer lexer(file_name, text);
	std::vector <Token> tokens = lexer.MakeTokens();

	std::pair<std::vector <Token>, IllegalCharError*> lex_res = {
		tokens,
		NULL
	};

	std::pair<bool, IllegalCharError*> error = lexer.getError();

	if (error.first) {
		lex_res.second = error.second;
	}

	if (lex_res.second != NULL) {
		std::cout << lex_res.second->As_string() << std::endl;
	}
	else {
		Parser* parser = new Parser(lex_res.first);

		ASTNode* ast = parser->parse();
		std::cout << ast->Represent() << std::endl;

		Interpreter* interpreter = new Interpreter();
		NodeValue* interpret_res = interpreter->Visit(ast);

		std::cout << interpret_res->Represent() << std::endl;
	}

	

	//return res;
}