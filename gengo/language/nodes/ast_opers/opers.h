#pragma once

class ASTNode;

/*--- Operation Nodes ---------------------------------------*/
// Binary Operator
class BinOpNode {
private:

public:
    ASTNode* left, * right;
    Token oper_token;

    BinOpNode(ASTNode* left, Token& oper_token, ASTNode* right);
    std::string Represent();
};

// Unary Operator
class UnOpNode {
private:

public:
    ASTNode* node;
    Token oper_token;

    UnOpNode(Token& oper_token, ASTNode* node);
    std::string Represent();
};