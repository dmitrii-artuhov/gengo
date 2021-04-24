#include "gengo.h"
#include "./language/run.h"

int main() {
	std::string FILE_NAME = "<console input>";

	while (true) {
		std::cout << "gengo > " << std::flush;
		std::string line;
		std::getline(std::cin, line);
		run(FILE_NAME, line);
	}	
	
	
	return 0;
}
