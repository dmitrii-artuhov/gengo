#pragma once


/*--- Type Nodes ---------------------------------------*/
// Integer Node
class IntNode {
private:
public:
    Token token;
    IntNode(Token& token);
    std::string Represent();
};

// Float Node
class FloatNode {
private:
public:
    Token token;
    FloatNode(Token& token);
    std::string Represent();
};