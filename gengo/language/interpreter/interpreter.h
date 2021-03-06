#pragma once

#include "../nodes/ast.h"
#include "../error/error.h"
#include "../context/context.h" // context.h file requires 'class NodeValue' definition



class NodeValue;
class IntNumber;
class FloatNumber;
class RunTimeResult; // run time


/*--- Interpreter ---------------------------------------------*/
class Interpreter {
private:
	RunTimeResult* RunTimeRes;

public:
	RunTimeResult* Visit(ASTNode* node, Context* context);

	RunTimeResult* VisitIntNode(ASTNode* node, Context* context);
	RunTimeResult* VisitFloatNode(ASTNode* node, Context* context);
	RunTimeResult* VisitStringNode(ASTNode* node, Context* context);

	RunTimeResult* VisitVarAssignNode(ASTNode* node, Context* context);
	RunTimeResult* VisitVarReassignNode(ASTNode* node, Context* context);
	RunTimeResult* VisitVarAccessNode(ASTNode* node, Context* context);

	RunTimeResult* VisitBinOpNode(ASTNode* node, Context* context);
	RunTimeResult* VisitUnOpNode(ASTNode* node, Context* context);

	RunTimeResult* VisitStatementsNode(ASTNode* node, Context* context);
	
	RunTimeResult* VisitArrayDeclNode(ASTNode* node, Context* context);
	RunTimeResult* VisitArrayAccessNode(ASTNode* node, Context* context);
	RunTimeResult* VisitArrayReassignNode(ASTNode* node, Context* context);

	RunTimeResult* VisitIfNode(ASTNode* node, Context* context);
	RunTimeResult* VisitForNode(ASTNode* node, Context* context);

	RunTimeResult* VisitFuncDeclNode(ASTNode* node, Context* context);
	RunTimeResult* VisitFuncCallNode(ASTNode* node, Context* context);
	RunTimeResult* VisitReturnNode(ASTNode* node, Context* context);
};





