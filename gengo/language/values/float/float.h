#pragma once

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
};

