#pragma once

#include "../tokens/position.h"

const std::string
ERROR_ILLEGAL_CHAR = "Illegal Character Error",
ERROR_INVALID_SYNTAX = "Invalid Syntax Error";


class Error {
private:
	std::string
		error_name,
		details;

	Position pos_start, pos_end;

public:
	Error(const std::string &error_name, std::string &details, Position &pos_start, Position &pos_end);
	std::string As_string();
};

