#pragma once

class ASTNode;


/*--- Statement Node --------------------------------------------------*/
class StatementsNode {
private:

public:
    std::vector <ASTNode*> nodes;

    StatementsNode(std::vector <ASTNode*>& nodes);
    std::string Represent();
};

