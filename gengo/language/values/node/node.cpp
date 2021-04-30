#include "../../../gengo.h"
#include "./node.h"
#include "../types.h"

#include "../../context/context.h"
#include "../../error/error.h"
#include "../../interpreter/runtime_result.h"

#include "../../../utils/utils.h"

#include "../int/int.h"
#include "../float/float.h"

/*--- Main value node ---------------------------------------*/
// constructors
NodeValue::NodeValue() {
	this->type = UNDEFIND_VALUE;
	this->value = nullptr;
	this->context = nullptr;
};
NodeValue::NodeValue(ASTNode* node) {
	this->context = nullptr;

	if (node->type == INT_NODE) {
		IntNode* curr_node = reinterpret_cast<IntNode*>(node->memory);
		long long val = cast_string_to_ll(curr_node->token.value);

		this->type = INT_VALUE;
		this->value = reinterpret_cast<void*> (new IntNumber(val));
	}
	else if (node->type == FLOAT_NODE) {
		FloatNode* curr_node = reinterpret_cast<FloatNode*>(node->memory);
		long double val = cast_string_to_ld(curr_node->token.value);

		this->type = FLOAT_VALUE;
		this->value = reinterpret_cast<void*> (new FloatNumber(val));
	}
	else {
		this->type = UNDEFIND_VALUE;
		this->value = nullptr;
	}
};
NodeValue::NodeValue(long long val) {
	this->context = nullptr;
	this->type = INT_VALUE;
	this->value = reinterpret_cast<void*> (new IntNumber(val));
}
NodeValue::NodeValue(long double val) {
	this->context = nullptr;
	this->type = FLOAT_VALUE;
	this->value = reinterpret_cast<void*> (new FloatNumber(val));
}

// internal methods
std::string NodeValue::Represent() {
	std::string res = "";

	if (this->type == INT_VALUE) {
		IntNumber* node = reinterpret_cast<IntNumber*>(this->value);
		res = std::to_string(node->value);
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* node = reinterpret_cast<FloatNumber*>(this->value);
		res = std::to_string(node->value);
	}

	return res;
}
NodeValue* NodeValue::SetContext(Context* context) {
	this->context = context;
	return this;
}

// operations
RunTimeResult* NodeValue::Add(NodeValue* other) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->Add(other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->Add(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}
RunTimeResult* NodeValue::Sub(NodeValue* other) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->Sub(other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->Sub(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}
RunTimeResult* NodeValue::Mult(NodeValue* other) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->Mult(other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->Mult(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}
RunTimeResult* NodeValue::Div(NodeValue* other) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->Div(other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->Div(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}

// static utils
NodeValue* NodeValue::CastToType(NodeValue* val, value_t cast_type) {
	if (cast_type == INT_VALUE) {
		if (val->type == INT_VALUE) return val;
		else if (val->type == FLOAT_VALUE) {
			FloatNumber* node = reinterpret_cast<FloatNumber*>(val->value);
			long long number = (long long)node->value;

			return new NodeValue(number);
		}
	}
	else if (cast_type == FLOAT_VALUE) {
		if (val->type == INT_VALUE) {
			IntNumber* node = reinterpret_cast<IntNumber*>(val->value);
			long double number = (long double)node->value;

			return new NodeValue(number);
		}
		else if (val->type == FLOAT_VALUE) return val;
	}
}
