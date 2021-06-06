#include "gengo.h"
#include "./language/run.h"
#include "./language/context/context.h"
#include "./language/values/values.h"


int main() {
	std::string mode = "";
	std::cout << "Pick reading mode: file(f) or console(c)" << std::endl;

	std::cin >> mode;

	if (mode == "c") {
		ConsoleInput();
	}
	else if (mode == "f") {
		std::cout << "Enter path to the file:" << std::endl;
		std::string path = "";

		std::cin >> path; // ../../../test.gengo
		FileInput(path);
	}
	
	return 0;
}

void ConsoleInput() {
	std::string FILE_NAME = "<console>";
	SymbolTable* global_table = new SymbolTable();
	global_table->parent = nullptr;

	Context* ctx = new Context(FILE_NAME, nullptr);
	ctx->symbol_table = global_table;

	ApplyBuiltInFunctions(ctx);

	while (true) {
		std::cout << "gengo > " << std::flush;
		std::string line;
		
		std::getline(std::cin, line);

		if (line == "exit") {
			break;
		}
		
		run(FILE_NAME, line, ctx);
	}
}


void FileInput(std::string &file_name) {
	std::string FILE_NAME = file_name;

	// manage file
	std::fstream file;
	file.open(FILE_NAME, std::ios::in);

	if (!file || !file.is_open()) {
		std::cout << "ERROR: no file found at '" + FILE_NAME + "'" << std::endl;
		return;
	}

	std::string text = "";
	std::string line = "";

	while (!file.eof()) {
		std::getline(file, line);
		text += line;
	}


	file.close();

	// start programm
	SymbolTable* global_table = new SymbolTable();
	global_table->parent = nullptr;

	Context* ctx = new Context(FILE_NAME, nullptr);
	ctx->symbol_table = global_table;

	ApplyBuiltInFunctions(ctx);

	run(FILE_NAME, text, ctx, false);
}


void ApplyBuiltInFunctions(Context* ctx) {
	/*
	##########################
	#   BUILT_IN FUNCTIONS   #
	##########################
	*/
	
	// Print
	ctx->symbol_table->Set(
		BUILT_IN_FUNCTION_PRINT,
		new NodeValue(ctx, BUILT_IN_FUNCTION_PRINT)
	);

	// Length
	ctx->symbol_table->Set(
		BUILT_IN_FUNCTION_LENGTH,
		new NodeValue(ctx, BUILT_IN_FUNCTION_LENGTH)
	);

	// Size
	ctx->symbol_table->Set(
		BUILT_IN_FUNCTION_SIZE,
		new NodeValue(ctx, BUILT_IN_FUNCTION_SIZE)
	);

	// Push
	ctx->symbol_table->Set(
		BUILT_IN_FUNCTION_PUSH,
		new NodeValue(ctx, BUILT_IN_FUNCTION_PUSH)
	);

	// Pop
	ctx->symbol_table->Set(
		BUILT_IN_FUNCTION_POP,
		new NodeValue(ctx, BUILT_IN_FUNCTION_POP)
	);
	

}