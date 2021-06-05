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

// String Node
class StringNode {
private:
public:
    Token token;
    StringNode(Token& token);
    std::string Represent();
};