#pragma once


#include "../../interpreter/runtime_result.h"
#include "../types.h"
#include "../../context/context.h"

class NodeValue {
private:

public:
	value_t type;
	void* value; // contains one of the classes below
	// (later strings and other entities will be added, so this will be handy, hopefully)
	Context* context;

	NodeValue();
	NodeValue(ASTNode* node);
	NodeValue(long long val);
	NodeValue(long double val);

	std::string Represent();
	NodeValue* SetContext(Context* ctx);

	RunTimeResult* Add(NodeValue* other);
	RunTimeResult* Sub(NodeValue* other);
	RunTimeResult* Mult(NodeValue* other);
	RunTimeResult* Div(NodeValue* other);

	static NodeValue* CastToType(NodeValue* val, value_t cast_type);
};
