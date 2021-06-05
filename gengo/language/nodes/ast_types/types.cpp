#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./types.h"


/*--- Type Nodes ---------------------------------------*/
// Integer Node
IntNode::IntNode(Token& token) : token(token) {}

std::string IntNode::Represent() {
    return this->token.Represent();
}

// Float Node
FloatNode::FloatNode(Token& token) : token(token) {}

std::string FloatNode::Represent() {
    return this->token.Represent();
}



// String Node
StringNode::StringNode(Token& token) : token(token) {}

std::string StringNode::Represent() {
    return this->token.Represent();
}

