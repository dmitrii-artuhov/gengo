#pragma once

class ASTNode;


/*--- Function declaration ---------------------------------------*/
class FuncDeclNode {
private:

public:
    std::string func_name;
    std::vector <std::pair <std::string, Token*>> args;
    Token* return_type;
    ASTNode* func_body;

    FuncDeclNode(std::string &func_name, std::vector <std::pair <std::string, Token*>> args, Token* return_type, ASTNode* func_body);
    std::string Represent();
};
