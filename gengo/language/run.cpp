/*--- Run - read text input ----------------------*/

#include "../gengo.h"
#include "./run.h"

#include "./tokens/token.h"
#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include "./interpreter/runtime_result.h"
#include "./interpreter/interpreter.h"
#include "./interpreter/runtime_result.h"
#include "./values/values.h"
#include "./context/context.h"



void run(std::string& file_name, std::string& text, Context* ctx, bool GENGO_LOG_TO_CONSOLE) {
	// Lexer
	Lexer lexer(file_name, text);
	LexerResult* lex_res = lexer.MakeTokens();

	if (lex_res->error) {
		std::cout << lex_res->error->As_string() << std::endl;
	}
	else if (GENGO_PARSE) {
		// Parser
		Parser* parser = new Parser(lex_res->tokens);

		ParseResult* parse_res = parser->parse();

		if (parse_res->error) {
			std::cout << parse_res->error->As_string() << std::endl;
		}
		else {
			if (GENGO_SHOW_AST) {
				std::cout << parse_res->ast->Represent() << std::endl;
			}

			// Interpreter
			if (GENGO_INTERPRET) {
				Interpreter* interpreter = new Interpreter();
				RunTimeResult* interpret_res = interpreter->Visit(parse_res->ast, ctx);

				if (interpret_res->error) {
					std::cout << interpret_res->error->As_string() << std::endl;
				}
				else if (GENGO_LOG_TO_CONSOLE && interpret_res->result) {
					std::cout << interpret_res->result->Represent() << std::endl;
				}
			}
		}
	}
}