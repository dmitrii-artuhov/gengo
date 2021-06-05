#include "../../../gengo.h"
#include "./node.h"
#include "../types.h"

#include "../../context/context.h"
#include "../../error/error.h"
#include "../../interpreter/runtime_result.h"

#include "../../../utils/utils.h"

#include "../int/int.h"
#include "../float/float.h"
#include "../function/functions.h"

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
	else if (node->type == FUNC_DECL_NODE) {
		FuncDeclNode* func = reinterpret_cast<FuncDeclNode*> (node->memory);

		this->type = FUNCTION_VALUE;
		this->value = reinterpret_cast<void*> (new Function(
			func->func_name,
			func->args,
			func->return_type,
			func->func_body,
			this->context
		));
	}
	else {
		this->type = UNDEFIND_VALUE;
		this->value = nullptr;
	}
};

NodeValue::NodeValue(Context* ctx, const std::string& func_name) {
	this->context = ctx;
	this->type = BUILT_IN_FUNCTION_VALUE;

	std::string name = func_name;

	if (name == BUILT_IN_FUNCTION_PRINT) {
		Token *arg_token = new Token(), 
			  *return_token = new Token();
		arg_token->type = return_token->type = TOKEN_TYPE;
		arg_token->value = return_token ->value = TYPE_INT;

		this->value = reinterpret_cast<void*> (new BuiltInFunction(
			name,
			std::vector <std::pair <std::string, Token*>>{ { std::string("value"), arg_token }},
			return_token,
			this->context
		));
	}
}


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

NodeValue* NodeValue::PropContext(Context* context) {
	if (this->type == FUNCTION_VALUE) {
		Function* node = reinterpret_cast<Function*>(this->value);
		node->context = context;
	}
	
	return this;
}

bool NodeValue::IsTrue() {
	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);

		if (curr->value == 0LL) return false;
		else return true;
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);

		if (curr->value == (long double)0) return false;
		else return true;
	}
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


RunTimeResult* NodeValue::AndedBy(NodeValue* other) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->AndedBy(other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->AndedBy(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}

RunTimeResult* NodeValue::OredBy(NodeValue* other) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->OredBy(other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->OredBy(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}

RunTimeResult* NodeValue::Notted() {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->Notted());
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->Notted());
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}

RunTimeResult* NodeValue::ComparedWith(Token& oper_token, NodeValue* other) {
	RunTimeResult* res = new RunTimeResult;

	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return res->Success(curr->ComparedWith(oper_token, other));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success(curr->ComparedWith(oper_token, other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type"),
			this->context
		));
	}
}


RunTimeResult* NodeValue::Execute(Interpreter* interpreter, std::vector <NodeValue*> &args) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type == FUNCTION_VALUE) {
		// make copy of the function instance to support recursion
		Function* func = reinterpret_cast<Function*> (this->value);

		NodeValue* return_val = res->Register(func->Copy()->Execute(interpreter, args));

		if (res->ShouldReturn())
			return res;

		return res->Success(return_val);
	}
	else if (this->type == BUILT_IN_FUNCTION_VALUE) {
		// make copy of the function instance to support recursion
		BuiltInFunction* func = reinterpret_cast<BuiltInFunction*> (this->value);

		NodeValue* return_val = res->Register(func->Copy()->Execute(args));

		if (res->ShouldReturn())
			return res;

		return res->Success(return_val);
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("'Execute' method is not supported for provided type"),
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
