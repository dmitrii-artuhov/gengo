#include "gengo.h"
#include "./language/run.h"
#include "./language/context/context.h"
#include "./language/values/values.h"

int main() {
	std::string FILE_NAME = "<console>";
	SymbolTable* global_table = new SymbolTable();
	global_table->parent = nullptr;

	Context* ctx = new Context(FILE_NAME, nullptr);
	ctx->symbol_table = global_table;

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


	while (true) {
		std::cout << "gengo > " << std::flush;
		std::string line;
		std::getline(std::cin, line);
		run(FILE_NAME, line, ctx);
	}
	
	
	return 0;
}
