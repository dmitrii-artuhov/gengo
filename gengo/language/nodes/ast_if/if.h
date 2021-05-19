#pragma once

class ASTNode;


/*--- If conditions ---------------------------------------*/
class IfNode {
private:

public:
    std::vector <std::pair <ASTNode*, ASTNode*>> cases;
    ASTNode* else_case;


    IfNode(std::vector <std::pair <ASTNode*, ASTNode*>>& cases,
        ASTNode* else_case);
    std::string Represent();
};
