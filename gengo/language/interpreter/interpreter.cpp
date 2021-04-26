#include "../../gengo.h"
#include "../../utils/utils.h"
#include "../interpreter/interpreter.h"
#include "../context/context.h"


/*--- Interpreter ---------------------------------------------*/

RunTimeResult* Interpreter::Visit(ASTNode* node, Context* context) {
	if (node->type == INT_NODE) {
		this->RunTimeRes = this->VisitIntNode(node, context);
	}
	else if (node->type == FLOAT_NODE) {
		this->RunTimeRes = this->VisitFloatNode(node, context);
	}
	else if (node->type == VAR_ASSIGN_NODE) {
		this->RunTimeRes = this->VisitVarAssignNode(node, context);
	}
	else if (node->type == VAR_ACCESS_NODE) {
		this->RunTimeRes = this->VisitVarAccessNode(node, context);
	}
	else if (node->type == BINOP_NODE) {
		this->RunTimeRes = this->VisitBinOpNode(node, context);
	}
	else if (node->type == UNOP_NODE) {
		this->RunTimeRes = this->VisitUnOpNode(node, context);
	}
	else {
		this->RunTimeRes->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined node type")
		));
	}

	return this->RunTimeRes;
}

RunTimeResult* Interpreter::VisitIntNode(ASTNode* node, Context* context) {
	return (new RunTimeResult())->Success(new NodeValue(node));
}
RunTimeResult* Interpreter::VisitFloatNode(ASTNode* node, Context* context) {
	//std::cout << "FloatNode\n";
	return (new RunTimeResult())->Success(new NodeValue(node));
}

RunTimeResult* Interpreter::VisitVarAssignNode(ASTNode* node, Context* context) {
	
	
	/*res = RTResult()
		var_name = node.var_name_tok.value
		value = res.register(self.visit(node.value_node, context))
		if res.error: return res

			context.symbol_table.set(var_name, value)
			return res.success(value)*/
}
RunTimeResult* Interpreter::VisitVarAccessNode(ASTNode* node, Context* context) {

}

RunTimeResult* Interpreter::VisitBinOpNode(ASTNode* node, Context* context) {
	//std::cout << "BinOpNode\n";

	BinOpNode* curr_node = reinterpret_cast<BinOpNode*>(node->memory);

	RunTimeResult* res = new RunTimeResult();

	NodeValue*  l_node = res->Register(this->Visit(curr_node->left, context));
	NodeValue* r_node = res->Register(this->Visit(curr_node->right, context));

	if (res->error) {
		return res;
	}

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
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined operation token"),
			curr_node->oper_token.pos_start,
			curr_node->oper_token.pos_end
		));
	}
}
RunTimeResult* Interpreter::VisitUnOpNode(ASTNode* node, Context* context) {
	//std::cout << "UnOpNode\n";

	RunTimeResult* res = new RunTimeResult();

	UnOpNode* curr_node = reinterpret_cast<UnOpNode*>(node->memory);
	NodeValue* r_node = res->Register(this->Visit(curr_node->node, context));

	if (curr_node->oper_token.type == TOKEN_MINUS) {
		NodeValue* oper_node = new NodeValue(-1LL);

		return oper_node->Mult(r_node);
	}

	return res->Success(r_node);
}



/*--- RunTimeResult -----------------------------------------*/

RunTimeResult::RunTimeResult() :
result(nullptr), error(nullptr) {}

RunTimeResult::RunTimeResult(NodeValue* node, Error* err) :
result(node), error(err) {}

RunTimeResult* RunTimeResult::Failure(Error* err) {
	this->error = err;
	return this;
}

RunTimeResult* RunTimeResult::Success(NodeValue* node) {
	this->result = node;
	return this;
}

NodeValue* RunTimeResult::Register(RunTimeResult* res) {
	if (res->error) {
		this->error = res->error;
	}
	return res->result;
}




/*--- Values ------------------------------------------------*/
/*--- Main value node ---------------------------------------*/
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
		return res->Success((curr->Add(other))->SetContext(this->context));
	}
	else if (this->type == FLOAT_VALUE) {
		FloatNumber* curr = reinterpret_cast<FloatNumber*>(this->value);
		return res->Success((curr->Add(other))->SetContext(this->context));
	}
	else {
		return res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined value type")
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
			std::string("Undefined value type")
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
			std::string("Undefined value type")
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
			std::string("Undefined value type")
		));
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