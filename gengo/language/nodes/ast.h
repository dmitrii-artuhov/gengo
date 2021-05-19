#pragma once

#include "../tokens/token.h"

// ast-nodes
#include "./ast_types/types.h"
#include "./ast_vars/vars.h"
#include "./ast_opers/opers.h"
#include "./ast_if/if.h"
#include "./ast_statements/statements.h"

enum node_t {
    INT_NODE,
    FLOAT_NODE,
    
    VAR_ASSIGN_NODE,
    VAR_REASSIGN_NODE,
    VAR_ACCESS_NODE,
    
    BINOP_NODE,
    UNOP_NODE,

    STATEMENTS_NODE,
    
    IF_NODE,

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

// If conditions
class IfNode;

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

    // if conditions
    ASTNode(std::vector <std::pair <ASTNode*, ASTNode*>> &cases, ASTNode* else_case);

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
