#include "../../gengo.h"
#include "../error/error.h"
#include "./runtime_result.h"



/*--- RunTimeResult -----------------------------------------*/

class NodeValue;

RunTimeResult::RunTimeResult() :
	result(nullptr), error(nullptr), return_val(false) {}

RunTimeResult::RunTimeResult(NodeValue* node, Error* err) :
	result(node), error(err), return_val(false) {}

RunTimeResult* RunTimeResult::Failure(Error* err) {
	this->error = err;
	return this;
}

RunTimeResult* RunTimeResult::Success(NodeValue* node) {
	this->result = node;
	return this;
}

NodeValue* RunTimeResult::Register(RunTimeResult* res) {
	if (res->error && !this->error) {
		this->error = res->error;
	}
	return res->result;
}

bool RunTimeResult::ShouldReturn() {
	if (this->error || this->return_val)
		return true;
	
	return false;
}



