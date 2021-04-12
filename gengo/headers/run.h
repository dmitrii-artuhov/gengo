#pragma once


#include "../headers/token.h"
#include "../headers/error.h"

std::pair<
	std::vector<Token>,
	IllegalCharError*
> run(std::string& text);