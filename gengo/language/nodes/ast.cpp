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
ASTNode::ASTNode(std::vector <ASTNode*>& nodes) {
    this->type = STATEMENTS_NODE;
    this->memory = reinterpret_cast<void*>(new StatementsNode(nodes));
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
// Assign
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


// Reassign
VarReassignNode::VarReassignNode(std::string& var_name, ASTNode* expr) :
    var_name(var_name), expr(expr) {}

std::string VarReassignNode::Represent() {
    std::string res = "";
    {
        res += "(IDENTIFIER:" + this->var_name + ", ";
        res += this->expr->Represent() + ")";
    }

    return res;
}


// Access
VarAccessNode::VarAccessNode(Token& token) :
    token(token), var_name(token.value) {}

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


/*--- Main Node --------------------------------------------------*/
StatementsNode::StatementsNode(std::vector <ASTNode*>& nodes):
    nodes(nodes) {}


std::string StatementsNode::Represent() {
    std::string res = "(";

    for (int i = 0; i < this->nodes.size(); i++) {
        ASTNode* node = this->nodes[i];

        res += node->type + ": " + node->Represent();
        if (i != this->nodes.size() - 1) res += ", ";
    }
    res += ")";
    return res;
}



/*--- UndefinedNode ----------------------------------------------*/
UndefinedNode::UndefinedNode(Token &token): token(token) {}

std::string UndefinedNode::Represent() {
    return this->token.Represent();
}
