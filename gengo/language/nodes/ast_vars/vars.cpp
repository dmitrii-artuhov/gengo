#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./vars.h"
#include "../ast.h"


/*--- Variable Nodes ----------------------------------------*/
// Assign
VarAssignNode::VarAssignNode(Token& token, std::string& var_name, ASTNode* expr) :
    token(token), var_name(var_name), expr(expr) {}


std::string VarAssignNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->token.Represent() + ", ";
        res += "IDENTIFIER:" + this->var_name + ", ";
        res += this->expr->Represent() + ")";
    }

    return res;
}


// Reassign
VarReassignNode::VarReassignNode(std::string& var_name, ASTNode* expr) :
    var_name(var_name), expr(expr) {}

std::string VarReassignNode::Represent() {
    std::string res = "";
    {
        res += "(IDENTIFIER:" + this->var_name + ", ";
        res += this->expr->Represent() + ")";
    }

    return res;
}


// Access
VarAccessNode::VarAccessNode(Token& token) :
    token(token), var_name(token.value) {}

std::string VarAccessNode::Represent() {
    std::string res = "";
    {
        res += "(" + this->token.Represent() + ")";
    }

    return res;
}
