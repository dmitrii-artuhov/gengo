#pragma once


#include "../../tokens/token.h"


class NodeValue;

class String {
private:
public:
	std::string value;

	String(std::string& val);

	// addition
	NodeValue* Add(NodeValue* other);

	// and
	NodeValue* AndedBy(NodeValue* other);

	// or
	NodeValue* OredBy(NodeValue* other);

	// not
	NodeValue* Notted();

	// and
	NodeValue* ComparedWith(Token& oper_token, NodeValue* other);
};
