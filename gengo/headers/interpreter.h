#pragma once

#include "./ast.h"

enum value_t {
	INT_VALUE,
	FLOAT_VALUE,
	UNDEFIND_VALUE
};
class NodeValue;
class IntNumber;
class FloatNumber;


class Interpreter {
private:

public:
	NodeValue* Visit(ASTNode* node);

	NodeValue* VisitIntNode(ASTNode* node);
	NodeValue* VisitFloatNode(ASTNode* node);
	NodeValue* VisitBinOpNode(ASTNode* node);
	NodeValue* VisitUnOpNode(ASTNode* node);
};

/*--- Values ---------------------------------------------*/


class NodeValue {
private:

public:
	value_t type;
	void* value; // contains one of the classes below
	// (later strings and other entities will be added, so this will be handy, hopefully)

	NodeValue();
	NodeValue(ASTNode* node);
	NodeValue(long long val);
	NodeValue(long double val);

	std::string Represent();


	NodeValue* Add(NodeValue* other);
	NodeValue* Sub(NodeValue* other);
	NodeValue* Mult(NodeValue* other);
	NodeValue* Div(NodeValue* other);
};

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


/*--- Interpreter ---------------------------------------------*/


