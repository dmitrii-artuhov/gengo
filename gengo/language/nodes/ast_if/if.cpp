#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./if.h"
#include "../ast.h"





/*--- If condition Node --------------------------------------------------*/
IfNode::IfNode(std::vector <std::pair <ASTNode*, ASTNode*>>& cases,
    ASTNode* else_case) : cases(cases), else_case(else_case) {}

std::string IfNode::Represent() {
    std::string res = "(";


    for (int i = 0; i < this->cases.size(); i++) {
        ASTNode
            * cond = this->cases[i].first,
            * stms = this->cases[i].second;

        res += "(CONDITION: ";
        res += cond->Represent();
        res += ", BODY: (";
        res += stms->Represent();
        res += ")";
    }

    if (else_case) {
        res += "(ELSE-CONDITION: ";
        res += else_case->Represent();
        res += ")";
    }

    res += ")";
    return res;
}
