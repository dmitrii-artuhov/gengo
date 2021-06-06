#pragma once


#include "../../tokens/token.h"
#include "../../context/context.h"
#include "../../interpreter/runtime_result.h"
#include "../../interpreter/interpreter.h"

class NodeValue;

class BaseFunction {
private:
public:
	Context *context; //  points to NodeValue context and works with it

	std::string func_name;
	std::vector <std::pair <std::string, Token*>> func_args; // { name, type }
	Token* return_type;

	BaseFunction(
		std::string &func_name,
		std::vector <std::pair <std::string, Token*>> args,
		Token* return_type,
		Context* passed_ctx
	);

	RunTimeResult* CheckArguments(std::vector <NodeValue*>& passed_args);
	RunTimeResult* PopulateArguments(std::vector <NodeValue*>& passed_args);
};


class Function : public BaseFunction {
private:
public:
	ASTNode* func_body;

	Function(
		std::string &func_name,
		std::vector <std::pair<std::string, Token*>>& args,
		Token* return_type,
		ASTNode* func_body,
		Context* passed_ctx
	);

	
	Function* Copy();
	RunTimeResult* Execute(Interpreter* interpreter, std::vector <NodeValue*>& args);
};

class BuiltInFunction : BaseFunction {
private:
public:
	BuiltInFunction(
		std::string& func_name,
		std::vector <std::pair<std::string, Token*>>& args,
		Token* return_type,
		Context* passed_ctx
	);

	BuiltInFunction* Copy();
	RunTimeResult* Execute(std::vector <NodeValue*>& args);

	/*--- Built-in functions ----------------*/
	// general
	RunTimeResult* Print();
	// strings
	RunTimeResult* Length();
	// arrays
	RunTimeResult* Size();
	RunTimeResult* Push();
	RunTimeResult* Pop();
};