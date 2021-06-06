#pragma once

#include "../tokens/token.h"

// ast-nodes
#include "./ast_types/types.h"
#include "./ast_vars/vars.h"
#include "./ast_opers/opers.h"
#include "./ast_if/if.h"
#include "./ast_for/for.h"
#include "./ast_array/array.h"
#include "./ast_statements/statements.h"
#include "./ast_functions/func.h"

enum node_t {
    INT_NODE,
    FLOAT_NODE,
    STRING_NODE,
    
    VAR_ASSIGN_NODE,
    VAR_REASSIGN_NODE,
    VAR_ACCESS_NODE,
    
    BINOP_NODE,
    UNOP_NODE,

    STATEMENTS_NODE,

    ARRAY_DECL_NODE,
    ARRAY_ACCESS_NODE,
    ARRAY_REASSIGN_NODE,
    
    IF_NODE,

    FOR_NODE,

    FUNC_DECL_NODE,
    FUNC_CALL_NODE, 
    RETURN_NODE,

    UNDEFIND_NODE,
};



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

    // statements/arrays
    ASTNode(std::vector <ASTNode*>& nodes, bool isArray=false);

    // if conditions
    ASTNode(std::vector <std::pair <ASTNode*, ASTNode*>> &cases, ASTNode* else_case);

    // for nodes
    ASTNode(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNode* body);

    // function nodes/arrays
    ASTNode(std::string &func_name, std::vector <std::pair <std::string, Token*>> &args, Token* return_type, ASTNode* func_body);
    ASTNode(std::string& func_name, std::vector <ASTNode*>& args, bool isArray=false); // functions/arrays
    ASTNode(ASTNode* expr); // return statement

    // array reassign
    ASTNode(std::string &name, std::vector <ASTNode*> &vec, ASTNode* new_val);

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
