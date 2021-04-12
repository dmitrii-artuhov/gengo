#include "gengo.h"
#include "headers/run.h"

int main() {
	while (true) {
		std::cout << "gengo > ";

		std::string line;
		std::getline(std::cin, line);

		std::pair<
			std::vector<Token>,
			IllegalCharError*
		> output = run(line);

		if (output.second != NULL) {
			std::cout << output.second->As_string() << std::endl;
		}
		else {
			for (Token token : output.first) {
				std::cout << token.Represent() << std::endl;
			}
		}
	}
	
	
	return 0;
}
