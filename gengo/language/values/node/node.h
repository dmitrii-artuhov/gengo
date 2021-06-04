#pragma once


#include "../../interpreter/runtime_result.h"
#include "../types.h"
#include "../../context/context.h"

class Interpreter;

class NodeValue {
private:

public:
	value_t type;
	void* value; // contains one of the value classes 
	// (later strings and other entities will be added, so this will be handy, hopefully)
	Context* context;

	NodeValue();
	NodeValue(ASTNode* node);
	NodeValue(long long val);
	NodeValue(long double val);

	std::string Represent();
	NodeValue* SetContext(Context* ctx);
	NodeValue* PropContext(Context* ctx);

	RunTimeResult* Add(NodeValue* other);
	RunTimeResult* Sub(NodeValue* other);
	RunTimeResult* Mult(NodeValue* other);
	RunTimeResult* Div(NodeValue* other);

	RunTimeResult* AndedBy(NodeValue* other);
	RunTimeResult* OredBy(NodeValue* other);
	RunTimeResult* Notted();
	RunTimeResult* ComparedWith(Token& oper_token, NodeValue* other);

	RunTimeResult* Execute(Interpreter* interpreter, std::vector <NodeValue*> &args);

	bool IsTrue();

	static NodeValue* CastToType(NodeValue* val, value_t cast_type);

	template <typename T, typename I>
	static bool Compare(Token& oper_token, T& a, I& b) {
		if (oper_token.type == TOKEN_EQEQ) {
			return a == b;
		}
		else if (oper_token.type == TOKEN_NE) {
			return a != b;
		}
		else if (oper_token.type == TOKEN_GT) {
			return a > b;
		}
		else if (oper_token.type == TOKEN_GTE) {
			return a >= b;
		}
		else if (oper_token.type == TOKEN_LT) {
			return a < b;
		}
		else if (oper_token.type == TOKEN_LTE) {
			return a <= b;
		}
	}
};
