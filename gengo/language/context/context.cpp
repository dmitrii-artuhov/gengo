#include "../../gengo.h"
#include "./context.h"



/*--- Symbol Table -------------------------------------------------*/

SymbolTable::SymbolTable() :
table({}), parent(nullptr) {}


SymbolTable::SymbolTable(SymbolTable* parent) :
table({}), parent(parent) {}


NodeValue* SymbolTable::Get(std::string key) {
	if (!this->table[key]) {
		if (this->parent != nullptr) return this->parent->Get(key);
		else return nullptr;
	}
	return this->table[key];
}


void SymbolTable::Set(std::string key, NodeValue* val) {
	this->table[key] = val;
}

void SymbolTable::Reset(std::string key, NodeValue* val) {
	if (!this->table[key]) {
		if (this->parent != nullptr)
			this->parent->Reset(key, val);
	}
	else
		this->table[key] = val;
}


void SymbolTable::Remove(std::string key) {
	this->table.erase(key);
}


/*--- Context -----------------------------------------*/
Context::Context():
	name(std::string("<undefined context>")),
	parent(nullptr),
	symbol_table(new SymbolTable())
{}

Context::Context(std::string &name, Context* parent) :
	name(name),
	parent(parent),
	symbol_table(new SymbolTable(parent ? parent->symbol_table : nullptr))
{}
