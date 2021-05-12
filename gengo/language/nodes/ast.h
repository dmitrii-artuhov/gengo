#pragma once

#include "../tokens/token.h"

enum node_t {
    INT_NODE,
    FLOAT_NODE,
    
    VAR_ASSIGN_NODE,
    VAR_REASSIGN_NODE,
    VAR_ACCESS_NODE,
    
    BINOP_NODE,
    UNOP_NODE,

    STATEMENTS_NODE,

    UNDEFIND_NODE,
};


// Main Node
class ASTNode;

// Type Nodes
class IntNode;
class FloatNode;

// Variables
class VarAssignNode;
class VarAccessNode;

// Operators Nodes
class BinOpNode;
class UnOpNode;

// Statements 
class StatementsNode;

/*--- Main Node --------------------------------------------------*/
class ASTNode {
private:

public:
    node_t type; // тип значения
    void* memory;

    // undefined
    ASTNode();
    // types and access variable
    ASTNode(Token &token);
    // variables
    ASTNode(Token& token, std::string &var_name, ASTNode* expr);
    ASTNode(std::string &var_name, ASTNode* expr);

    // operators
    ASTNode(ASTNode* left, Token& token, ASTNode* right);
    ASTNode(Token& token, ASTNode* node);

    // statements
    ASTNode(std::vector <ASTNode*>& nodes);

    std::string Represent();
};

/*--- Type Nodes ---------------------------------------*/
// Integer Node
class IntNode {
private:
public:
    Token token;
    IntNode(Token &token);
    std::string Represent();
};

// Float Node
class FloatNode {
private:
public:
    Token token;
    FloatNode(Token &token);
    std::string Represent();
};

/*--- Variables ---------------------------------------*/
// Assign
class VarAssignNode {
private:
public:
    Token token; // { TOKEN_TYPE, int|float }
    std::string var_name; // name
    ASTNode* expr;

    VarAssignNode(Token &token, std::string &var_name, ASTNode* expr);
    std::string Represent();
};
// Reassign
class VarReassignNode {
private:
public:
    std::string var_name;
    ASTNode* expr;

    VarReassignNode(std::string& var_name, ASTNode* expr);
    std::string Represent();
};
// access
class VarAccessNode {
private:
public:
    Token token; // { TOKEN_INDETIFIER, var_name }
    std::string var_name; // name

    VarAccessNode(Token& token);
    std::string Represent();
};



/*--- Operation Nodes ---------------------------------------*/
// Binary Operator
class BinOpNode {
private:

public:
    ASTNode *left, *right;
    Token oper_token;

    BinOpNode(ASTNode* left, Token &oper_token, ASTNode* right);
    std::string Represent();
};

// Unary Operator
class UnOpNode {
private:

public:
    ASTNode *node;
    Token oper_token;

    UnOpNode(Token& oper_token, ASTNode *node);
    std::string Represent();
};



/*--- Main Node --------------------------------------------------*/
class StatementsNode {
private:

public:
    std::vector <ASTNode*> nodes;

    StatementsNode(std::vector <ASTNode*>& nodes);
    std::string Represent();
};


/*--- Undefined Node ---------------------------------------*/
class UndefinedNode {
private:

public:
    Token token;

    UndefinedNode(Token& token);
    std::string Represent();
};
