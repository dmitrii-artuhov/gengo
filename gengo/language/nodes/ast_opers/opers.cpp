#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./opers.h"
#include "../ast.h"



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
UnOpNode::UnOpNode(Token& oper_token, ASTNode* node) :
    node(node), oper_token(oper_token) {}


std::string UnOpNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->oper_token.type + ", ";
        res += this->node->Represent() + ")";
    }

    return res;
}

