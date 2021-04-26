#include "gengo.h"
#include "./language/run.h"
#include "./language/context/context.h"

int main() {
	std::string FILE_NAME = "<console input>";
	SymbolTable* global_table = new SymbolTable();
	global_table->parent = nullptr;

	while (true) {
		std::cout << "gengo > " << std::flush;
		std::string line;
		std::getline(std::cin, line);
		run(FILE_NAME, line, global_table);
	}
	
	
	return 0;
}
