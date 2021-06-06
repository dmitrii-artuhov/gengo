#include "../../gengo.h"
#include "../tokens/token.h"
#include "../nodes/ast.h"

// ast-nodes
#include "./ast_types/types.h"
#include "./ast_vars/vars.h"
#include "./ast_opers/opers.h"
#include "./ast_if/if.h"
#include "./ast_statements/statements.h"
#include "./ast_for/for.h"
#include "./ast_functions/func.h"
#include "./ast_array/array.h"



/*--- Main Node --------------------------------------------------*/
// undefined
ASTNode::ASTNode() {
	this->type = UNDEFIND_NODE;
	this->memory = nullptr;
}

// types
ASTNode::ASTNode(Token &token) {
    const std::string t = token.type;


    if (t == TOKEN_INT) {
        this->type = INT_NODE;
        this->memory = reinterpret_cast<void*>(new IntNode(token));
    }
    else if (t == TOKEN_FLOAT) {
        this->type = FLOAT_NODE;
        this->memory = reinterpret_cast<void*>(new FloatNode(token));
    }
    else if (t == TOKEN_STRING) {
        this->type = STRING_NODE;
        this->memory = reinterpret_cast<void*>(new StringNode(token));
    }
    else if (t == TOKEN_IDENTIFIER) {
        this->type = VAR_ACCESS_NODE;
        this->memory = reinterpret_cast<void*>(new VarAccessNode(token));
    }
    else {
        this->type = UNDEFIND_NODE;
        this->memory = nullptr;
    }
}

// variables
ASTNode::ASTNode(Token &token, std::string &var_name, ASTNode* expr) {
    this->type = VAR_ASSIGN_NODE;
    this->memory = reinterpret_cast<void*>(new VarAssignNode(token, var_name, expr));
}

ASTNode::ASTNode(std::string& var_name, ASTNode* expr) {
    this->type = VAR_REASSIGN_NODE;
    this->memory = reinterpret_cast<void*>(new VarReassignNode(var_name, expr));
}


// operators
// binary
ASTNode::ASTNode(ASTNode* left, Token& token, ASTNode* right) {
    const std::string t = token.type;

    if (t == TOKEN_PLUS    ||
        t == TOKEN_MINUS   ||
        t == TOKEN_DIV     ||
        t == TOKEN_MULT    ||

        t == TOKEN_AND     ||
        t == TOKEN_OR      ||
        t == TOKEN_EQEQ    ||
        t == TOKEN_GT      ||
        t == TOKEN_GTE     ||
        t == TOKEN_LT      ||
        t == TOKEN_NE      ||
        t == TOKEN_LTE     
       ) {
        this->type = BINOP_NODE;
        this->memory = reinterpret_cast<void*>(new BinOpNode(left, token, right));
    }
    else {
        this->type = UNDEFIND_NODE;
        this->memory = nullptr;
    }
}

// unary
ASTNode::ASTNode(Token& token, ASTNode* node) {
    const std::string t = token.type;

    if (t == TOKEN_PLUS || t == TOKEN_MINUS || t == TOKEN_NOT) {
        this->type = UNOP_NODE;
        this->memory = reinterpret_cast<void*>(new UnOpNode(token, node));
    }
    else {
        this->type = UNDEFIND_NODE;
        this->memory = nullptr;
    }
}

// statements
ASTNode::ASTNode(std::vector <ASTNode*>& nodes, bool isArray) {
    if (!isArray) {
        this->type = STATEMENTS_NODE;
        this->memory = reinterpret_cast<void*>(new StatementsNode(nodes));
    }
    else {
        this->type = ARRAY_DECL_NODE;
        this->memory = reinterpret_cast<void*>(new ArrayDeclNode(nodes));
    }
}

// arrays


// if conditions
ASTNode::ASTNode(std::vector <std::pair <ASTNode*, ASTNode*>>& cases, ASTNode* else_case) {
    this->type = IF_NODE;
    this->memory = reinterpret_cast<void*>(new IfNode(cases, else_case));
}


// for nodes
ASTNode::ASTNode(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNode* body) {
    this->type = FOR_NODE;
    this->memory = reinterpret_cast <void*>(new ForNode(init, cond, inc, body));
}

// function nodes / arrays
ASTNode::ASTNode(std::string &func_name, std::vector <std::pair <std::string, Token*>> &args, Token* return_type, ASTNode* func_body) {
    this->type = FUNC_DECL_NODE;
    this->memory = reinterpret_cast<void*>(new FuncDeclNode(func_name, args, return_type, func_body));
}

ASTNode::ASTNode(std::string& func_name, std::vector <ASTNode*>& args, bool isArray) {
    if (!isArray) {
        this->type = FUNC_CALL_NODE;
        this->memory = reinterpret_cast<void*>(new FuncCallNode(func_name, args));
    }
    else {
        this->type = ARRAY_ACCESS_NODE;
        this->memory = reinterpret_cast<void*>(new ArrayAccessNode(func_name, args));
    }
}

ASTNode::ASTNode(ASTNode* expr) {
    this->type = RETURN_NODE;
    this->memory = reinterpret_cast<void*>(new ReturnNode(expr));
}

// array reassign
ASTNode::ASTNode(std::string& name, std::vector <ASTNode*>& vec, ASTNode* new_val) {
    this->type = ARRAY_REASSIGN_NODE;
    this->memory = reinterpret_cast<void*> (new ArrayReassignNode(name, vec, new_val));
}

// methods
std::string ASTNode::Represent() {
    std::string res = "";

    if (this->type == INT_NODE) {
        IntNode* node = reinterpret_cast<IntNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == FLOAT_NODE) {
        FloatNode* node = reinterpret_cast<FloatNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == STRING_NODE) {
        StringNode* node = reinterpret_cast<StringNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == VAR_ASSIGN_NODE) {
        VarAssignNode* node = reinterpret_cast<VarAssignNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == VAR_REASSIGN_NODE) {
        VarReassignNode* node = reinterpret_cast<VarReassignNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == VAR_ACCESS_NODE) {
        VarAccessNode* node = reinterpret_cast<VarAccessNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == BINOP_NODE) {
        BinOpNode* node = reinterpret_cast<BinOpNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == UNOP_NODE) {
        UnOpNode* node = reinterpret_cast<UnOpNode*>(this->memory);
        res += node->Represent();
    }
    else if (this->type == STATEMENTS_NODE) {
        StatementsNode* node = reinterpret_cast<StatementsNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == ARRAY_DECL_NODE) {
        ArrayDeclNode* node = reinterpret_cast<ArrayDeclNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == ARRAY_ACCESS_NODE) {
        ArrayAccessNode* node = reinterpret_cast<ArrayAccessNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == ARRAY_REASSIGN_NODE) {
        ArrayReassignNode* node = reinterpret_cast<ArrayReassignNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == IF_NODE) {
        IfNode* node = reinterpret_cast<IfNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == FOR_NODE) {
        ForNode* node = reinterpret_cast<ForNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == FUNC_DECL_NODE) {
        FuncDeclNode* node = reinterpret_cast<FuncDeclNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == FUNC_CALL_NODE) {
        FuncCallNode* node = reinterpret_cast<FuncCallNode*> (this->memory);
        res += node->Represent();
    }
    else if (this->type == RETURN_NODE) {
        ReturnNode* node = reinterpret_cast<ReturnNode*> (this->memory);
        res += node->Represent();
    }

    return res;
}

/*--- UndefinedNode ----------------------------------------------*/
UndefinedNode::UndefinedNode(Token &token): token(token) {}

std::string UndefinedNode::Represent() {
    return this->token.Represent();
}
