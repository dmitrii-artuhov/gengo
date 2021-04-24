/*--- Run - read text input ----------------------*/

#include "../gengo.h"
#include "./run.h"

#include "./tokens/token.h"
//#include "./error/error.h"
#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include "./interpreter/interpreter.h"



void run(std::string& file_name, std::string& text) {
	// Lexer
	Lexer lexer(file_name, text);
	LexerResult* lex_res = lexer.MakeTokens();

	if (lex_res->error) {
		std::cout << lex_res->error->As_string() << std::endl;
	}
	else {
		// Parser
		Parser* parser = new Parser(lex_res->tokens);

		ParseResult* parse_res = parser->parse();

		if (parse_res->error) {
			std::cout << parse_res->error->As_string() << std::endl;
		}
		else {
			std::cout << parse_res->ast->Represent() << std::endl;

			// Interpreter
			Interpreter* interpreter = new Interpreter();
			NodeValue* interpret_res = interpreter->Visit(parse_res->ast);

			std::cout << interpret_res->Represent() << std::endl;
		}
	}
}