#pragma once

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
};
