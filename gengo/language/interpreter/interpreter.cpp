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
	else if (node->type == FOR_NODE) {
		this->RunTimeRes = this->VisitForNode(node, context);
	}
	else if (node->type == FUNC_DECL_NODE) {
		this->RunTimeRes = this->VisitFuncDeclNode(node, context);
	}
	else if (node->type == FUNC_CALL_NODE) {
		this->RunTimeRes = this->VisitFuncCallNode(node, context);
	}
	else if (node->type == RETURN_NODE) {
		this->RunTimeRes = this->VisitReturnNode(node, context);
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

	if (res->ShouldReturn()) {
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

	if (res->ShouldReturn()) {
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


	if (res->ShouldReturn()) {
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
	if (res->ShouldReturn()) {
		return res;
	}

	NodeValue* r_node = res->Register(this->Visit(curr_node->right, context));

	if (res->ShouldReturn()) {
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

	RunTimeResult* res = new RunTimeResult();

	for (int i = 0; i < nodes.size(); i++) {
		res = this->Visit(nodes[i], context);

		if (res->ShouldReturn()) {
			return res;
		}
	}

	return res;
}

// Visit if nodes
RunTimeResult* Interpreter::VisitIfNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();
	// set correct context 
	Context* curr_context = new Context(std::string("<condition>"), context);
	curr_context->symbol_table = new SymbolTable();
	curr_context->symbol_table->parent = context->symbol_table;

	IfNode* ast = reinterpret_cast<IfNode*> (node->memory);

	for (std::pair <ASTNode*, ASTNode*> p : ast->cases) {
		NodeValue* condition_value = res->Register(this->Visit(p.first, curr_context));
		if (res->ShouldReturn())
			return res;

		if (condition_value->IsTrue()) {
			NodeValue* expr_val = res->Register(this->Visit(p.second, curr_context));
			if (res->ShouldReturn())
				return res;
			return res->Success(expr_val);
		}
	}

	if (ast->else_case) {
		NodeValue* expr_val = res->Register(this->Visit(ast->else_case, curr_context));
		if (res->ShouldReturn())
			return res;
		return res->Success(expr_val);
	}

	return res->Success(NULL);
}


// Visit for node
RunTimeResult* Interpreter::VisitForNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();
	// set correct context 
	Context* curr_context = new Context(std::string("<loop>"), context);
	curr_context->symbol_table = new SymbolTable();
	curr_context->symbol_table->parent = context->symbol_table;

	ForNode* ast = reinterpret_cast<ForNode*> (node->memory);

	// initialization
	NodeValue* init = nullptr;
	if (ast->init != nullptr) {
		init = res->Register(this->Visit(ast->init, curr_context));
		if (res->ShouldReturn())
			return res;
	}

	// condition 

	NodeValue* cond = res->Register(this->Visit(ast->cond, curr_context));
	if (res->ShouldReturn())
		return res;

	while (cond->IsTrue()) {
		// increment
		if (ast->inc != nullptr) {
			res->Register(this->Visit(ast->inc, curr_context));
			if (res->ShouldReturn())
				return res;
		}

		res->Register(this->Visit(ast->body, curr_context));
		if (res->ShouldReturn())
			return res;

		// condition - is not optimized well
		// (figure out a better way of doing this)
		cond = res->Register(this->Visit(ast->cond, curr_context));
		if (res->ShouldReturn())
			return res;
	}

	return res->Success(NULL);
}


// Visit functions
RunTimeResult* Interpreter::VisitFuncDeclNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();
	NodeValue* func_value = new NodeValue(node);
	
	// init function context
	FuncDeclNode* func = reinterpret_cast<FuncDeclNode*> (node->memory);
	func_value->context = new Context(func->func_name, context);
	func_value->context->symbol_table = new SymbolTable(context->symbol_table);
	func_value->PropContext(func_value->context);


	context->symbol_table->Set(func->func_name, func_value);
	return res->Success(func_value);
}


RunTimeResult* Interpreter::VisitFuncCallNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();

	// get call-node
	FuncCallNode* func = reinterpret_cast<FuncCallNode*> (node->memory);
	// collect arguments
	std::vector <NodeValue*> args;

	// search for this function
	NodeValue* exec_func = context->symbol_table->Get(func->func_name);

	// does not exist
	if (exec_func == nullptr) {
		return res->Failure(new Error(
			ERROR_RUNTIME,
			std::string("Function '" + func->func_name +"' is not declared in this scope"),
			context
		));
	}
	// exists but is not a function
	else if (exec_func->type != FUNCTION_VALUE && exec_func->type != BUILT_IN_FUNCTION_VALUE) {
		return res->Failure(new Error(
			ERROR_RUNTIME,
			std::string("'" + func->func_name + "' is not a function"),
			context
		));
	}

	// collect arguments
	for (ASTNode* a : func->args) {
		NodeValue* val = res->Register(this->Visit(a, context));

		if (res->ShouldReturn())
			return res;

		args.push_back(val);
	}

	NodeValue* return_val = res->Register(exec_func->Execute(this, args));
	

	if (res->ShouldReturn())
		return res;

	return res->Success(return_val);
}


RunTimeResult* Interpreter::VisitReturnNode(ASTNode* node, Context* context) {
	RunTimeResult* res = new RunTimeResult();

	ReturnNode* return_node = reinterpret_cast<ReturnNode*> (node->memory);

	NodeValue* return_val = res->Register(this->Visit(return_node->expr, context));

	if (res->ShouldReturn())
		return res;

	res->return_val = true;

	return res->Success(return_val);
}


