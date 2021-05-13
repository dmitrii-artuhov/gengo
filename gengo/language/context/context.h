#pragma once

#include "../../gengo.h"
//#include "../interpreter/interpreter.h"

class NodeValue;


/*--- Symbol Table -------------------------------------------------*/
class SymbolTable {
private:
public:
	std::unordered_map <std::string, NodeValue*> table;

	SymbolTable* parent;
	SymbolTable();

	NodeValue* Get(std::string key);
	void Set(std::string key, NodeValue* val);
	void Reset(std::string key, NodeValue* val);
	void Remove(std::string key);
};



/*--- Context -----------------------------------------*/
class Context {
private:
public:
	std::string name;
	Context* parent;
	SymbolTable* symbol_table;

	Context();
	Context(std::string &name, Context* parent);
};

