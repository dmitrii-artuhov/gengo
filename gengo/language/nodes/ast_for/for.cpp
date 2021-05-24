#include "../../../gengo.h"
#include "./for.h"
#include "../ast.h"


ForNode::ForNode(ASTNode* init, ASTNode* cond, ASTNode* inc, ASTNode* body) :
    init(init), cond(cond), inc(inc), body(body) {}

std::string ForNode::Represent() {
    std::string res = "(LOOP: ";

    res += "(";
    if (this->init) {
        res += "INIT: ";
        res += this->init->Represent();
    }

    if (this->cond) {
        res += "; ";
        res += "COND: ";
        res += this->cond->Represent();
    }

    if (this->inc) {
        res += "; ";
        res += "INC: ";
        res += this->inc->Represent();
    }


    if (this->body) {
        res += "; ";
        res += "BODY: ";
        res += this->body->Represent();
    }

    res += ")";

    return res;
}