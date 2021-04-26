#pragma once

#include "../../gengo.h"
#include "../interpreter/interpreter.h"

// unordered_map <key, NodeValue*>

class SymbolTable {
private:
public:
	std::unordered_map <std::string, NodeValue*> table;
	SymbolTable* parent;

	SymbolTable();

	NodeValue* Get(std::string key);
	void Set(std::string key, NodeValue* val);
	void Remove(std::string key);
};
