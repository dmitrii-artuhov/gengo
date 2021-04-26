#include "../../gengo.h"
#include "../tokens/token.h"
#include "../nodes/ast.h"




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


// operators
// binary
ASTNode::ASTNode(ASTNode* left, Token& token, ASTNode* right) {
    const std::string t = token.type;

    if (t == TOKEN_PLUS || t == TOKEN_MINUS || t == TOKEN_DIV || t == TOKEN_MULT) {
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

    if (t == TOKEN_PLUS || t == TOKEN_MINUS) {
        this->type = UNOP_NODE;
        this->memory = reinterpret_cast<void*>(new UnOpNode(token, node));
    }
    else {
        this->type = UNDEFIND_NODE;
        this->memory = nullptr;
    }
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
    else if (this->type == VAR_ASSIGN_NODE) {
        VarAssignNode* node = reinterpret_cast<VarAssignNode*>(this->memory);
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

    return res;
}

/*--- Type Nodes ---------------------------------------*/
// Integer Node
IntNode::IntNode(Token& token) : token(token) {}

std::string IntNode::Represent() {
    return this->token.Represent();
}

// Float Node
FloatNode::FloatNode(Token& token): token(token) {}

std::string FloatNode::Represent() {
    return this->token.Represent();
}


/*--- Variable Nodes ----------------------------------------*/
VarAssignNode::VarAssignNode(Token& token, std::string& var_name, ASTNode* expr) :
token(token), var_name(var_name), expr(expr) {}

std::string VarAssignNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->token.Represent() + ", ";
        res += "IDENTIFIER:" + this->var_name + ", ";
        res += this->expr->Represent() + ")";
    }

    return res;
}


VarAccessNode::VarAccessNode(Token& token) :
    token(token) {}

std::string VarAccessNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->token.Represent() + ")";
    }

    return res;
}


/*--- Operation Nodes ---------------------------------------*/
// Binary Operator
BinOpNode::BinOpNode(ASTNode* left, Token& oper_token, ASTNode* right) :
    left(left), right(right), oper_token(oper_token) {}


std::string BinOpNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->left->Represent() + ", ";
        res += this->oper_token.type + ", ";
        res += this->right->Represent() + ")";
    }

    return res;
}

// Unary Operator
UnOpNode::UnOpNode(Token& oper_token, ASTNode *node) :
    node(node), oper_token(oper_token) {}


std::string UnOpNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->oper_token.type + ", ";
        res += this->node->Represent() + ")";
    }

    return res;
}

/*--- UndefinedNode ----------------------------------------------*/
UndefinedNode::UndefinedNode(Token &token): token(token) {}

std::string UndefinedNode::Represent() {
    return this->token.Represent();
}
