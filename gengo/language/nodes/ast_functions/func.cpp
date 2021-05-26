#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./func.h"
#include "../ast.h"

FuncDeclNode::FuncDeclNode(std::string& func_name, std::vector <std::pair <std::string, Token*>> args, Token* return_type, ASTNode* func_body):
	func_name(func_name), args(args), return_type(return_type), func_body(func_body) {}


std::string FuncDeclNode::Represent() {
	std::string res = "(";

	res += "FUNC: (NAME: " + this->func_name
		+ "; RTYPE: " + this->return_type->value
		+ "; ARGS: ";

	for (std::pair <std::string, Token*> p : this->args) {
		res += "(" + p.first + ", " + p.second->value + ") ";
	}
	
	res += "; BODY: " + this->func_body->Represent();

	return res;
}