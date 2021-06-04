#include "../../../gengo.h"
#include "../../tokens/token.h"
#include "./func.h"
#include "../ast.h"


/*--- Function declaration ---------------------------------------*/

FuncDeclNode::FuncDeclNode(std::string& func_name, std::vector <std::pair <std::string, Token*>> args, Token* return_type, ASTNode* func_body):
	func_name(func_name), args(args), return_type(return_type), func_body(func_body) {}


std::string FuncDeclNode::Represent() {
	std::string res = "(";

	res += "FUNC: (NAME: " + this->func_name
		+ "; RTYPE: " + this->return_type->value
		+ "; ARGS: ";


	for (int i = 0; i < this->args.size(); i++) {
		std::pair <std::string, Token*> p = this->args[i];

		res += "(" + p.first + ":" + p.second->value + ")";

		if (i != this->args.size() - 1)
			res += ", ";
	}
	
	res += "; BODY: " + this->func_body->Represent();

	res += "))";

	return res;
}


/*--- Function Call ---------------------------------------*/
FuncCallNode::FuncCallNode(std::string& func_name, std::vector <ASTNode*> args) :
	func_name(func_name), args(args) {}


std::string FuncCallNode::Represent() {
	std::string res = "(";

	res += "FUNC: (NAME: " + this->func_name
		+ "; ARGS: ";


	for (int i = 0; i < this->args.size(); i++) {
		ASTNode* p = this->args[i];
		
		res += p->Represent();

		if (i != this->args.size() - 1)
			res += ", ";
	}

	res += "))";

	return res;
}


/*--- Return Node -----------------------------------------------*/
ReturnNode::ReturnNode(ASTNode* expr) : expr(expr) {}

std::string ReturnNode::Represent() {
	std::string res = "(RETURN: (";

	res += this->expr->Represent();

	res += "))";

	return res;
}


