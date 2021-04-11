#include "gengo.h"

int main() {
	while (true) {
		std::cout << "gengo > ";

		std::string line;
		std::getline(std::cin, line);
		std::cout << line << std::endl;
	}
	
	
	return 0;
}
