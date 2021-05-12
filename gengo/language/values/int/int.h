#pragma once


#include "../../tokens/token.h"

class NodeValue;

class IntNumber {
private:
public:
	long long value;

	IntNumber(long long val);

	// addition
	NodeValue* Add(NodeValue* other);

	// subtraction
	NodeValue* Sub(NodeValue* other);

	// multiplication
	NodeValue* Mult(NodeValue* other);

	// division
	NodeValue* Div(NodeValue* other);

	// and
	NodeValue* AndedBy(NodeValue* other);

	// or
	NodeValue* OredBy(NodeValue* other);

	// not
	NodeValue* Notted();

	// and
	NodeValue* ComparedWith(Token& oper_token, NodeValue* other);
};
