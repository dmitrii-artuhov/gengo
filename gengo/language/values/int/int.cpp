#include "../../../gengo.h"
#include "./int.h"
#include "../types.h"
#include "../node/node.h"
#include "../float/float.h"


/*--- IntNumber ---------------------------------------*/
IntNumber::IntNumber(long long val) : value(val) {}

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

