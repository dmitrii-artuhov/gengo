#pragma once

class ASTNode;


/*--- For loops ---------------------------------------*/
class ForNode {
private:

public:
    ASTNode *init,
            *cond,
            *inc,
            *body;

    ForNode(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNode* body);
    std::string Represent();
};
