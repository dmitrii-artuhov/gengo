#include "../../gengo.h"
#include "./symbol_table.h"


SymbolTable::SymbolTable() :
table({}), parent(nullptr) {}


NodeValue* SymbolTable::Get(std::string key) {
	if (!this->table[key]) {
		return this->parent->Get(key);
	}
	return this->table[key];
}


void SymbolTable::Set(std::string key, NodeValue* val) {
	this->table[key] = val;
}


void SymbolTable::Remove(std::string key) {
	this->table.erase(key);
}


