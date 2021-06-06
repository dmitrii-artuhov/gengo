#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./array.h"
#include "../ast.h"






/*--- Array Decl Node --------------------------------------------------*/
ArrayDeclNode::ArrayDeclNode(std::vector <ASTNode*>& vec) : body(vec) {}

std::string ArrayDeclNode::Represent() {
    std::string res = "[";

    for (int i = 0; i < this->body.size(); i++) {
        res += this->body[i]->Represent();

        if (i != this->body.size() - 1)
            res += ", ";
    }
    
    res += "]";
    return res;
}



/*--- Array access node ----------------------------------------------*/
ArrayAccessNode::ArrayAccessNode(std::string& array_name, std::vector<ASTNode*> &array_indexes) :
    array_name(array_name), array_indexes(array_indexes) {}


std::string ArrayAccessNode::Represent() {
    std::string res = "(";

    res += "ARRAY_NAME:" + this->array_name + ", ";

    for (int i = 0; i < this->array_indexes.size(); i++) {
        res += "INDEX: (" + this->array_indexes[i]->Represent() + ")";

        if (i != this->array_indexes.size() - 1)
            res += ", ";
    }

    res += ")";

    return res;
}


/*--- Array reassign Node ---------------------------------*/
ArrayReassignNode::ArrayReassignNode(std::string& name, std::vector <ASTNode*>& vec, ASTNode* new_val) :
    array_name(name), array_indexes(vec), new_val(new_val) {}


std::string ArrayReassignNode::Represent() {
    std::string res = "(";

    res += "ARRAY_NAME:" + this->array_name + ", ";

    for (int i = 0; i < this->array_indexes.size(); i++) {
        res += "INDEX: (" + this->array_indexes[i]->Represent() + ")";

        if (i != this->array_indexes.size() - 1)
            res += ", ";
    }

    res += ", ";

    res += "NEW_VALUE: (" + this->new_val->Represent() + ")";

    res += ")";

    return res;
}









