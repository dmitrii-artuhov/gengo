#pragma once


#include "./tokens/token.h"
#include "./error/error.h"
#include "./context/context.h"

/*std::pair<
	std::vector<Token>,
	IllegalCharError*
>*/
void run(std::string& file_name, std::string& text, Context* ctx, bool GENGO_LOG_TO_CONSOLE=true);