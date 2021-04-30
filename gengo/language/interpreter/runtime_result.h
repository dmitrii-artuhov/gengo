#pragma once

#include "../error/error.h"

/*--- RunTimeResult -----------------------------------------*/
class NodeValue;

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
