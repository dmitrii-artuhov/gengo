#pragma once

#include "../tokens/position.h"
#include "../nodes/ast.h"
#include "../context/context.h"

const std::string
ERROR_ILLEGAL_CHAR = "Illegal Character Error",
ERROR_INVALID_SYNTAX = "Invalid Syntax Error",
ERROR_INTERNAL = "Internal Error",
ERROR_RUNTIME = "Run Time Error";


class Error {
private:
	std::string
		error_name,
		details;

	Position pos_start, pos_end;

	// Only for RunTimeError
	Context* context;

public:
	Error(const std::string &error_name, std::string &details, Position &pos_start, Position &pos_end);
	Error(const std::string& error_name, std::string& details); // change this line with below one
	Error(const std::string& error_name, std::string& details, Context* ctx);

	std::string As_string();
	std::string Traceback();
};

