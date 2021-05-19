#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./statements.h"
#include "../ast.h"




/*--- Statements Node --------------------------------------------------*/
StatementsNode::StatementsNode(std::vector <ASTNode*>& nodes) :
    nodes(nodes) {}


std::string StatementsNode::Represent() {
    std::string res = "(";

    for (int i = 0; i < this->nodes.size(); i++) {
        ASTNode* node = this->nodes[i];

        res += "STATEMENT: " + node->Represent();
        if (i != this->nodes.size() - 1) res += ", ";
    }
    res += ")";
    return res;
}