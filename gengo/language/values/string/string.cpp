#include "../../../gengo.h"
#include "./string.h"
#include "../types.h"
#include "../node/node.h"
#include "../int/int.h"
#include "../float/float.h"
#include "../../tokens/token.h"


class NodeValue;




/*--- String ---------------------------------------*/
// constructors
String::String(std::string& s) : value(s) {}

// operations
// addition
NodeValue* String::Add(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		std::string res = this->value + std::to_string(neigh->value);
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		std::string res = this->value + std::to_string(neigh->value);
		return new NodeValue(res);
	}
	else if (other->type == STRING_NODE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		std::string res = this->value + neigh->value;
		return new NodeValue(res);
	}
}

// and
NodeValue* String::AndedBy(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value.size() && neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long long res = this->value.size() && neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == STRING_NODE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		long long res = this->value.size() && neigh->value.size();
		return new NodeValue(res);
	}
}

// or
NodeValue* String::OredBy(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value.size() || neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long long res = this->value.size() || neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == STRING_NODE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		long long res = this->value.size() && neigh->value.size();
		return new NodeValue(res);
	}
}

// not
NodeValue* String::Notted() {
	long long res = !(this->value.size());

	return new NodeValue(res);
}

// and
NodeValue* String::ComparedWith(Token& oper_token, NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = (long long)NodeValue::Compare(oper_token, this->value, std::to_string(neigh->value));
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long long res = (long long)NodeValue::Compare(oper_token, this->value, std::to_string(neigh->value));
		return new NodeValue(res);
	}
	else if (other->type == STRING_VALUE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		long long res = (long long)NodeValue::Compare(oper_token, this->value, neigh->value);
		return new NodeValue(res);
	}
}