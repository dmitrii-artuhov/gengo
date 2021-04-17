#include "gengo.h"
#include "headers/run.h"
#include "headers/parser.h"

int main() {
	std::string FILE_NAME = "<console input>";

	while (true) {
		std::cout << "gengo > ";

		std::string line;
		std::getline(std::cin, line);

		std::pair<
			std::vector<Token>,
			IllegalCharError*
		> output = run(FILE_NAME, line);

		if (output.second != NULL) {
			std::cout << output.second->As_string() << std::endl;
		}
		else {
			Parser *parser = new Parser(output.first);

			ASTNode* ast = parser->parse();
			std::cout << ast->Represent() << std::endl;
		}
	}	
	
	
	return 0;
}
