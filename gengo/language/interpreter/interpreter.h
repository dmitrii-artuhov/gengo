#pragma once

#include "../nodes/ast.h"
#include "../error/error.h"
#include "../context/context.h" // context.h file requires 'class NodeValue' definition



enum value_t {
	INT_VALUE,
	FLOAT_VALUE,
	UNDEFIND_VALUE
};


class NodeValue;
class IntNumber;
class FloatNumber;



class RunTimeResult; // run time


/*--- Interpreter ---------------------------------------------*/
class Interpreter {
private:
	RunTimeResult* RunTimeRes;

public:
	RunTimeResult* Visit(ASTNode* node, Context* context);

	RunTimeResult* VisitIntNode(ASTNode* node, Context* context);
	RunTimeResult* VisitFloatNode(ASTNode* node, Context* context);

	RunTimeResult* VisitVarAssignNode(ASTNode* node, Context* context);
	RunTimeResult* VisitVarAccessNode(ASTNode* node, Context* context);

	RunTimeResult* VisitBinOpNode(ASTNode* node, Context* context);
	RunTimeResult* VisitUnOpNode(ASTNode* node, Context* context);
};


/*--- RunTimeResult -----------------------------------------*/
class RunTimeResult {
private:
public:
	NodeValue* result;
	Error* error;

	RunTimeResult();
	RunTimeResult(NodeValue* node, Error* err);

	RunTimeResult* Failure(Error* err);
	RunTimeResult* Success(NodeValue* node);
	NodeValue* Register(RunTimeResult* res);
};





/*--- Values ---------------------------------------------*/
class NodeValue {
private:

public:
	value_t type;
	void* value; // contains one of the classes below
	// (later strings and other entities will be added, so this will be handy, hopefully)
	Context *context;

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



