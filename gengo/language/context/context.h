#pragma once

#include "../../gengo.h"
#include "../symbol_table/symbol_table.h"

class Context {
private:
public:
	std::string name;
	Context* parent;
	SymbolTable* symbol_table;

	Context();
	Context(std::string &name, Context* parent);
};