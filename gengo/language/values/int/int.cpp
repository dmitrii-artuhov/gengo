#include "../../../gengo.h"
#include "./int.h"
#include "../types.h"
#include "../node/node.h"
#include "../float/float.h"
#include "../string/string.h"
#include "../../tokens/token.h"



class NodeValue;

/*--- IntNumber ---------------------------------------*/
// constructors
IntNumber::IntNumber(long long val) : value(val) {}

// operations
// addition
NodeValue* IntNumber::Add(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value + neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long double res = (long double)this->value + neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == STRING_VALUE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		std::string res = std::to_string(this->value) + neigh->value;
		return new NodeValue(res);
	}
}
// subtraction
NodeValue* IntNumber::Sub(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value - neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long double res = (long double)this->value - neigh->value;
		return new NodeValue(res);
	}
}
// multiplication
NodeValue* IntNumber::Mult(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value * neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long double res = (long double)this->value * neigh->value;
		return new NodeValue(res);
	}
}
// division
NodeValue* IntNumber::Div(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		if (neigh->value == 0) {
			// error
			return new NodeValue((long double)0);
		}
		else {
			long long res = this->value / neigh->value;
			return new NodeValue(res);
		}
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		if (neigh->value == (long double)0.) {
			// error
			return new NodeValue((long double)0);
		}
		else {
			long double res = (long double)this->value / neigh->value;
			return new NodeValue(res);
		}
	}
}

// and
NodeValue* IntNumber::AndedBy(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value && neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long long res = this->value && neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == STRING_VALUE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		long long res = this->value && neigh->value.size();
		return new NodeValue(res);
	}
}

// or
NodeValue* IntNumber::OredBy(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = this->value || neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long long res = this->value || neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == STRING_VALUE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		long long res = this->value || neigh->value.size();
		return new NodeValue(res);
	}
}

// not
NodeValue* IntNumber::Notted() {
	long long res = !(this->value);

	return new NodeValue(res);
}

// and
// fix this shit
NodeValue* IntNumber::ComparedWith(Token& oper_token, NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long long res = (long long)NodeValue::Compare(oper_token, this->value, neigh->value);
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long long res = (long long)NodeValue::Compare(oper_token, this->value, neigh->value);
		return new NodeValue(res);
	}
	else if (other->type == STRING_VALUE) {
		String* neigh = reinterpret_cast<String*>(other->value);

		long long res = (long long)NodeValue::Compare(oper_token, std::to_string(this->value), neigh->value);
		return new NodeValue(res);
	}
}