#include "../../../gengo.h"
#include "./node.h"
#include "../types.h"

#include "../../context/context.h"
#include "../../error/error.h"
#include "../../interpreter/runtime_result.h"

#include "../../../utils/utils.h"

#include "../int/int.h"
#include "../float/float.h"
#include "../string/string.h"
#include "../array/array.h"
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
	else if (node->type == STRING_NODE) {
		StringNode* curr_node = reinterpret_cast<StringNode*>(node->memory);
		std::string val = curr_node->token.value;

		this->type = STRING_VALUE;
		this->value = reinterpret_cast<void*> (new String(val));
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
	std::string name = func_name;

	this->context = new Context(name, ctx);
	this->type = BUILT_IN_FUNCTION_VALUE;

	if (name == BUILT_IN_FUNCTION_PRINT) {
		Token *arg_token = new Token(), 
			  *return_token = new Token();
		arg_token->type = return_token->type = TOKEN_TYPE;
		arg_token->value = return_token ->value = TYPE_STRING;

		this->value = reinterpret_cast<void*> (new BuiltInFunction(
			name,
			std::vector <std::pair <std::string, Token*>>{ { std::string("value"), arg_token }},
			return_token,
			this->context
		));
	}
	else if (name == BUILT_IN_FUNCTION_LENGTH) {
		Token* arg_token = new Token(),
			* return_token = new Token();
		arg_token->type = return_token->type = TOKEN_TYPE;
		arg_token->value = TYPE_STRING, return_token->value = TYPE_INT;

		this->value = reinterpret_cast<void*> (new BuiltInFunction(
			name,
			std::vector <std::pair <std::string, Token*>>{ { std::string("value"), arg_token }},
			return_token,
			this->context
		));
	}
	else if (name == BUILT_IN_FUNCTION_SIZE) {
		Token* arg_token = new Token(),
			* return_token = new Token();
		arg_token->type = return_token->type = TOKEN_TYPE;
		arg_token->value = TYPE_ARRAY, return_token->value = TYPE_INT;

		this->value = reinterpret_cast<void*> (new BuiltInFunction(
			name,
			std::vector <std::pair <std::string, Token*>>{ { std::string("value"), arg_token }},
			return_token,
			this->context
		));
	}
	else if (name == BUILT_IN_FUNCTION_PUSH) {
		Token* arg_token_1 = new Token(),
			* arg_token_2 = new Token(),
			* return_token = new Token();

		arg_token_1->type = arg_token_2->type = return_token->type = TOKEN_TYPE;

		arg_token_1->value = TYPE_ARRAY;
		arg_token_2->value = TYPE_ANY;
		return_token->value = TYPE_ANY;

		this->value = reinterpret_cast<void*> (new BuiltInFunction(
			name,
			std::vector <std::pair <std::string, Token*>>{
				{ std::string("array"), arg_token_1 },
				{ std::string("element"), arg_token_2 }
			},
			return_token,
			this->context
		));
	}
	else if (name == BUILT_IN_FUNCTION_POP) {
		Token* arg_token_1 = new Token(),
			* arg_token_2 = new Token(),
			* return_token = new Token();

		arg_token_1->type = arg_token_2->type = return_token->type = TOKEN_TYPE;

		arg_token_1->value = TYPE_ARRAY;
		arg_token_2->value = TYPE_INT;
		return_token->value = TYPE_ANY;

		this->value = reinterpret_cast<void*> (new BuiltInFunction(
			name,
			std::vector <std::pair <std::string, Token*>>{
				{ std::string("array"), arg_token_1 },
				{ std::string("index"), arg_token_2 }
			},
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
NodeValue::NodeValue(std::string& val) {
	this->context = nullptr;
	this->type = STRING_VALUE;
	this->value = reinterpret_cast<void*> (new String(val));
}
NodeValue::NodeValue(std::vector <NodeValue*>& vec) {
	this->context = nullptr;
	this->type = ARRAY_VALUE;
	this->value = reinterpret_cast<void*> (new Array(vec));
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
	else if (this->type == STRING_VALUE) {
		String* node = reinterpret_cast<String*>(this->value);
		res = node->value;
	}
	else if (this->type == ARRAY_VALUE) {
		Array* node = reinterpret_cast<Array*> (this->value);
		res = node->Represent();
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

RunTimeResult* NodeValue::GetElementByIndex(std::vector <NodeValue*>&indexes) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type != ARRAY_VALUE) {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Invalid type provided"),
			this->context
		));
	}

	// fill vector with ints, they point to indexes of the array
	std::vector <long long> int_indexes;

	for (NodeValue* val : indexes) {
		if (val->type != INT_VALUE) {
			return res->Failure(new Error(
				ERROR_RUNTIME,
				std::string("Array index must be an integer"),
				this->context
			));
		}

		IntNumber* int_val = reinterpret_cast<IntNumber*> (val->value);
		int_indexes.push_back(int_val->value);
	}

	if (int_indexes.size() == 0) {
		return res->Failure(new Error(
			ERROR_RUNTIME,
			std::string("Expected index value"),
			context
		));
	}

	Array* _array = reinterpret_cast<Array*> (this->value);
	NodeValue* found_val = res->Register(_array->GetElementByIndex(int_indexes, context));

	if (res->ShouldReturn())
		return res;

	return res->Success(found_val);
}

RunTimeResult* NodeValue::ReassingElementByIndex(std::vector <NodeValue*>& indexes, NodeValue* new_val) {
	RunTimeResult* res = new RunTimeResult();

	if (this->type != ARRAY_VALUE) {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Invalid type provided"),
			this->context
		));
	}

	// fill vector with ints, they point to indexes of the array
	std::vector <long long> int_indexes;

	for (NodeValue* val : indexes) {
		if (val->type != INT_VALUE) {
			return res->Failure(new Error(
				ERROR_RUNTIME,
				std::string("Array index must be an integer"),
				this->context
			));
		}

		IntNumber* int_val = reinterpret_cast<IntNumber*> (val->value);
		int_indexes.push_back(int_val->value);
	}

	if (int_indexes.size() == 0) {
		return res->Failure(new Error(
			ERROR_RUNTIME,
			std::string("Expected index value"),
			context
		));
	}

	Array* _array = reinterpret_cast<Array*> (this->value);
	NodeValue* reassigned_val = res->Register(_array->ReassingElementByIndex(int_indexes, new_val, this->context));

	if (res->ShouldReturn())
		return res;

	return res->Success(reassigned_val);
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
	else if (this->type == STRING_VALUE) {
		String* curr = reinterpret_cast<String*>(this->value);
		return res->Success(curr->Add(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Provided type does not support '+' operator"),
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
			std::string("Provided type does not support '-' operator"),
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
			std::string("Provided type does not support '*' operator"),
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
			std::string("Provided type does not support '/' operator"),
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
	else if (this->type == STRING_VALUE) {
		String* curr = reinterpret_cast<String*>(this->value);
		return res->Success(curr->AndedBy(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Provided type does not support 'and' operator"),
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
	else if (this->type == STRING_VALUE) {
		String* curr = reinterpret_cast<String*>(this->value);
		return res->Success(curr->OredBy(other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Provided type does not support 'or' operator"),
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
	else if (this->type == STRING_VALUE) {
		String* curr = reinterpret_cast<String*>(this->value);
		return res->Success(curr->Notted());
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Provided type does not support 'not' operator"),
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
	else if (this->type == STRING_VALUE) {
		String* curr = reinterpret_cast<String*>(this->value);
		return res->Success(curr->ComparedWith(oper_token, other));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Provided type does not support compare operators"),
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
		else {
			return val;
		}
	}
	else if (cast_type == FLOAT_VALUE) {
		if (val->type == INT_VALUE) {
			IntNumber* node = reinterpret_cast<IntNumber*>(val->value);
			long double number = (long double)node->value;

			return new NodeValue(number);
		}
		else if (val->type == FLOAT_VALUE) return val;
		else {
			return val;
		}
	}
	else if (cast_type == STRING_VALUE) {
		if (val->type == INT_VALUE) {
			IntNumber* node = reinterpret_cast<IntNumber*>(val->value);
			std::string str = std::to_string(node->value);

			return new NodeValue(str);
		}
		else if (val->type == FLOAT_VALUE) {
			FloatNumber* node = reinterpret_cast<FloatNumber*>(val->value);
			std::string str = std::to_string(node->value);

			return new NodeValue(str);
		}
		else if (val->type == STRING_NODE) return val;
		else {
			return val;
		}
	}
	else {
		return val;
	}
}
