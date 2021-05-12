#include "../../../gengo.h"
#include "./float.h"
#include "../types.h"
#include "../node/node.h"
#include "../int/int.h"
#include "../../tokens/token.h"



class NodeValue;

/*--- FloatNumber ---------------------------------------*/
// constructors
FloatNumber::FloatNumber(long double val) : value(val) {}

// operations
// addition
NodeValue* FloatNumber::Add(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long double res = this->value + (long double)neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long double res = this->value + neigh->value;
		return new NodeValue(res);
	}
}
// subtraction
NodeValue* FloatNumber::Sub(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long double res = this->value - (long double)neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long double res = this->value - neigh->value;
		return new NodeValue(res);
	}
}
// multiplication
NodeValue* FloatNumber::Mult(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		long double res = this->value * (long double)neigh->value;
		return new NodeValue(res);
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		long double res = this->value * neigh->value;
		return new NodeValue(res);
	}
}
// division
NodeValue* FloatNumber::Div(NodeValue* other) {
	if (other->type == INT_VALUE) {
		IntNumber* neigh = reinterpret_cast<IntNumber*>(other->value);

		if (other->value == 0) {
			// error
			return new NodeValue((long double)0);
		}
		else {
			long double res = this->value / (long double)neigh->value;
			return new NodeValue(res);
		}
	}
	else if (other->type == FLOAT_VALUE) {
		FloatNumber* neigh = reinterpret_cast<FloatNumber*>(other->value);

		if (neigh->value == 0.) {
			// error
			return new NodeValue((long double)0);
		}
		else {
			long double res = this->value / neigh->value;
			return new NodeValue(res);
		}
	}
}

// and
NodeValue* FloatNumber::AndedBy(NodeValue* other) {
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
}

// or
NodeValue* FloatNumber::OredBy(NodeValue* other) {
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
}

// not
NodeValue* FloatNumber::Notted() {
	long long res = !(this->value);

	return new NodeValue(res);
}

// and
// fix this shit
NodeValue* FloatNumber::ComparedWith(Token& oper_token, NodeValue* other) {
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
}