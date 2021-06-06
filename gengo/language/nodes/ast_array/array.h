#pragma once

class ASTNode;


/*--- Array ---------------------------------------*/
class ArrayDeclNode {
private:

public:
    std::vector <ASTNode*> body;

    ArrayDeclNode(std::vector <ASTNode*>& vec);
    std::string Represent();
};



class ArrayAccessNode {
private:

public:
    std::string array_name;
    std::vector<ASTNode*> array_indexes; // must be integers

    ArrayAccessNode(std::string& array_name, std::vector<ASTNode*> &array_indexes);

    std::string Represent();
};




class ArrayReassignNode {
private:
public:
    std::string array_name;
    std::vector<ASTNode*> array_indexes; // must be integers
    ASTNode* new_val;

    ArrayReassignNode(std::string& name, std::vector <ASTNode*>& vec, ASTNode* new_val);
    std::string Represent();
};