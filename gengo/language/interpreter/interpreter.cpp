#include "../../gengo.h"
#include "../../utils/utils.h"
#include "../interpreter/interpreter.h"


/*--- Interpreter ---------------------------------------------*/

NodeValue* Interpreter::Visit(ASTNode* node) {
	if (node->type == INT_NODE) {
		return this->VisitIntNode(node);
	}
	else if (node->type == FLOAT_NODE) {
		return this->VisitFloatNode(node);
	}
	else if (node->type == BINOP_NODE) {
		return this->VisitBinOpNode(node);
	}
	else if (node->type == UNOP_NODE) {
		return this->VisitUnOpNode(node);
	}
	else {
		std::cout << "Error! Undefined node type\n";
		// error
		return nullptr;
	}
}
NodeValue* Interpreter::VisitIntNode(ASTNode* node) {
	//std::cout << "IntNode\n";
	return new NodeValue(node);
}
NodeValue* Interpreter::VisitFloatNode(ASTNode* node) {
	//std::cout << "FloatNode\n";
	return new NodeValue(node);
}
NodeValue* Interpreter::VisitBinOpNode(ASTNode* node) {
	//std::cout << "BinOpNode\n";

	BinOpNode* curr_node = reinterpret_cast<BinOpNode*>(node->memory);

	NodeValue*  l_node = this->Visit(curr_node->left);
	NodeValue* r_node = this->Visit(curr_node->right);

	std::string t = curr_node->oper_token.type;
	if (t == TOKEN_PLUS) {
		return l_node->Add(r_node);
	}
	else if (t == TOKEN_MINUS) {
		return l_node->Sub(r_node);
	}
	else if (t == TOKEN_MULT) {
		return l_node->Mult(r_node);
	}
	else if (t == TOKEN_DIV) {
		return l_node->Div(r_node);
	}
	else {
		// error, hopefully we don't reach here
	}

}
NodeValue* Interpreter::VisitUnOpNode(ASTNode* node) {
	//std::cout << "UnOpNode\n";

	UnOpNode* curr_node = reinterpret_cast<UnOpNode*>(node->memory);

	if (curr_node->oper_token.type == TOKEN_MINUS) {
		NodeValue* r_node = this->Visit(curr_node->node);
		NodeValue* oper_node = new NodeValue(-1LL);

		return oper_node->Mult(r_node);
	}
}





/*--- Values ------------------------------------------------*/
/*--- Main value node ---------------------------------------*/
NodeValue::NodeValue() {
	this->type = UNDEFIND_VALUE;
	this->value = nullptr;
};
NodeValue::NodeValue(ASTNode* node) {	
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
	this->type = INT_VALUE;
	this->value = reinterpret_cast<void*> (new IntNumber(val));
}
NodeValue::NodeValue(long double val) {
	this->type = FLOAT_VALUE;
	this->value = reinterpret_cast<void*> (new FloatNumber(val));
}

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

// operations
NodeValue* NodeValue::Add(NodeValue* other) {
	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return curr->Add(other);
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return curr->Add(other);
	}
	else {
		// error, undefined value type
	}
}
NodeValue* NodeValue::Sub(NodeValue* other) {
	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return curr->Sub(other);
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return curr->Sub(other);
	}
}
NodeValue* NodeValue::Mult(NodeValue* other) {
	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return curr->Mult(other);
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return curr->Mult(other);
	}
}
NodeValue* NodeValue::Div(NodeValue* other) {
	if (this->type == INT_VALUE) {
		IntNumber* curr = reinterpret_cast<IntNumber*>(this->value);
		return curr->Div(other);
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return curr->Div(other);
	}
}


IntNumber::IntNumber(long long val) : value(val) {}
FloatNumber::FloatNumber(long double val) : value(val) {}

/*--- IntNumber ---------------------------------------*/
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



/*--- FloatNumber ---------------------------------------*/
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