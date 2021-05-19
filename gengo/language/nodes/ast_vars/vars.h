#pragma once


class ASTNode;

/*--- Variables ---------------------------------------*/
// Assign
class VarAssignNode {
private:
public:
    Token token; // { TOKEN_TYPE, int|float }
    std::string var_name; // name
    ASTNode* expr;

    VarAssignNode(Token& token, std::string& var_name, ASTNode* expr);
    std::string Represent();
};
// Reassign
class VarReassignNode {
private:
public:
    std::string var_name;
    ASTNode* expr;

    VarReassignNode(std::string& var_name, ASTNode* expr);
    std::string Represent();
};
// access
class VarAccessNode {
private:
public:
    Token token; // { TOKEN_INDETIFIER, var_name }
    std::string var_name; // name

    VarAccessNode(Token& token);
    std::string Represent();
};

