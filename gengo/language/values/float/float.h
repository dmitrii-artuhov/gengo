#pragma once

#include "../../tokens/token.h"
/*--- Values ---------------------------------------------*/

class NodeValue;

class FloatNumber {
private:
public:
	long double value;

	FloatNumber(long double val);

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

