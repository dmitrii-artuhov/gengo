#include "../../gengo.h"
#include "./context.h"


Context::Context():
	name(std::string("<undefined context>")), parent(nullptr), symbol_table({})
{}

Context::Context(std::string &name, Context* parent) :
	name(name), parent(parent), symbol_table({})
{}