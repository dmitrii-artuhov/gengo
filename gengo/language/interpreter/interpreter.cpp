#include "../../gengo.h"
#include "../../utils/utils.h"
#include "./runtime_result.h"
#include "../interpreter/interpreter.h"

#include "../values/values.h"


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
	else if (node->type == VAR_REASSIGN_NODE) {
		this->RunTimeRes = this->VisitVarReassignNode(node, context);
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
	else if (node->type == STATEMENTS_NODE) {
		this->RunTimeRes = this->VisitStatementsNode(node, context);
	}
	else if (node->type == IF_NODE) {
		this->RunTimeRes = this->VisitIfNode(node, context);
	}
	else {
		RunTimeResult* res = new RunTimeResult();
		this->RunTimeRes = res->Failure(new Error(
			ERROR_INTERNAL,
			std::string("Undefined node type"),
			context
		));
	}

	return this->RunTimeRes;
}

// Visit basic types nodes
RunTimeResult* Interpreter::VisitIntNode(ASTNode* node, Context* context) {
	NodeValue* res = new NodeValue(node);
	return (new RunTimeResult())->Success(res->SetContext(context));
}
RunTimeResult* Interpreter::VisitFloatNode(ASTNode* node, Context* context) {
	NodeValue* res = new NodeValue(node);
	return (new RunTimeResult())->Success(res->SetContext(context));
	// return (new RunTimeResult())->Success(new NodeValue(node));
}

// Visit variables
RunTimeResult* Interpreter::VisitVarAssignNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();

	VarAssignNode* var_node = reinterpret_cast<VarAssignNode*>(node->memory);

	NodeValue* val = res->Register(this->Visit(var_node->expr, context));

	if (res->error) {
		return res;
	}

	// casting variables to specified types
	NodeValue* casted_val;

	if (var_node->token.value == TYPE_INT) {
		casted_val = NodeValue::CastToType(val, INT_VALUE);
	}
	else if (var_node->token.value == TYPE_FLOAT) {
		casted_val = NodeValue::CastToType(val, FLOAT_VALUE);
	}

	context->symbol_table->Set(var_node->var_name, casted_val);
	return res->Success(casted_val);
}
RunTimeResult* Interpreter::VisitVarReassignNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();

	VarReassignNode* var_node = reinterpret_cast<VarReassignNode*>(node->memory);

	// casting variables to specified types
	NodeValue* var_stored = context->symbol_table->Get(var_node->var_name);
	if (!var_stored) {
		return res->Failure(new Error(
			ERROR_RUNTIME,
			std::string("'" + var_node->var_name + "' is not defined"),
			context
		));
	}

	NodeValue* val = res->Register(this->Visit(var_node->expr, context));

	if (res->error) {
		return res;
	}

	// casting variables to specified types
	NodeValue* casted_val;

	if (var_stored->type == INT_VALUE) {
		casted_val = NodeValue::CastToType(val, INT_VALUE);
	}
	else if (var_stored->type == FLOAT_VALUE) {
		casted_val = NodeValue::CastToType(val, FLOAT_VALUE);
	}


	if (res->error) {
		return res;
	}

	context->symbol_table->Reset(var_node->var_name, casted_val);
	return res->Success(casted_val);
}
RunTimeResult* Interpreter::VisitVarAccessNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();

	VarAccessNode* var_node = reinterpret_cast<VarAccessNode*>(node->memory);
	NodeValue* val = context->symbol_table->Get(var_node->var_name);

	if (!val) {
		// Add context here
		return res->Failure(new Error(
			ERROR_RUNTIME,
			std::string("'" + var_node->var_name + "' is not defined"),
			context
		));
	}


	return res->Success(val);
}

// Visit operators
RunTimeResult* Interpreter::VisitBinOpNode(ASTNode* node, Context* context) {
	//std::cout << "BinOpNode\n";

	BinOpNode* curr_node = reinterpret_cast<BinOpNode*>(node->memory);

	RunTimeResult* res = new RunTimeResult();

	NodeValue*  l_node = res->Register(this->Visit(curr_node->left, context));
	if (this->RunTimeRes->error) {
		return this->RunTimeRes;
	}

	NodeValue* r_node = res->Register(this->Visit(curr_node->right, context));

	if (this->RunTimeRes->error) {
		return this->RunTimeRes;
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
	else if (t == TOKEN_AND) {
		return l_node->AndedBy(r_node);
	}
	else if (t == TOKEN_OR) {
		return l_node->OredBy(r_node);
	}
	else if (t == TOKEN_GT  ||
			t == TOKEN_GTE  ||
			t == TOKEN_LT   ||
			t == TOKEN_LTE  ||
			t == TOKEN_EQEQ ||
			t == TOKEN_NE) {
		return l_node->ComparedWith(curr_node->oper_token, r_node);
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
	else if (curr_node->oper_token.type == TOKEN_NOT) {
		return r_node->Notted();
	}

	return res->Success(r_node);
}

// Visit statements
RunTimeResult* Interpreter::VisitStatementsNode(ASTNode* node, Context* context) {
	StatementsNode* ast = reinterpret_cast<StatementsNode*> (node->memory);
	std::vector <ASTNode*> nodes = ast->nodes;

	RunTimeResult* res;

	for (int i = 0; i < nodes.size(); i++) {
		res = this->Visit(nodes[i], context);

		if (res->error) {
			return res;
		}
	}

	return res;
}

// Visite if nodes
RunTimeResult* Interpreter::VisitIfNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();
	// set correct context 
	Context* curr_context = new Context(std::string("<condition>"), context);
	curr_context->symbol_table = new SymbolTable();
	curr_context->symbol_table->parent = context->symbol_table;

	IfNode* ast = reinterpret_cast<IfNode*> (node->memory);

	for (std::pair <ASTNode*, ASTNode*> p : ast->cases) {
		NodeValue* condition_value = res->Register(this->Visit(p.first, curr_context));
		if (res->error)
			return res;

		if (condition_value->IsTrue()) {
			NodeValue* expr_val = res->Register(this->Visit(p.second, curr_context));
			if (res->error)
				return res;
			return res->Success(expr_val);
		}
	}

	if (ast->else_case) {
		NodeValue* expr_val = res->Register(this->Visit(ast->else_case, curr_context));
		if (res->error)
			return res;
		return res->Success(expr_val);
	}

	return res->Success(NULL);
}