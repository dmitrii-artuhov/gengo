#pragma once

#include "token.h"

enum node_t {
    INT_NODE,
    FLOAT_NODE,
    BINOP_NODE,
    UNOP_NODE,
    UNDEFIND_NODE,
};


// Main Node
class ASTNode;
// Type Nodes
class IntNode;
class FloatNode;
// Function Nodes
class BinOpNode;
class UnOpNode;

/*--- Main Node --------------------------------------------------*/
class ASTNode {
private:

public:
    node_t type; // тип значения
    void* memory;

    // undefined
    ASTNode();
    // types
    ASTNode(Token &token);
    // operators
    ASTNode(ASTNode* left, Token& token, ASTNode* right);
    ASTNode(Token& token, ASTNode* node);

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