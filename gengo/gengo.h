#pragma once
/*--- Global Libs ---------------*/

#include <iostream>
#include <cassert>
#include <any>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>


const bool GENGO_SHOW_TOKENS = !true;
const bool GENGO_SHOW_AST = !true;
//const bool GENGO_LOG_TO_CONSOLE = true;


const bool GENGO_PARSE = true;
const bool GENGO_INTERPRET = true;



void ConsoleInput();
void FileInput(std::string &file_name);

class Context;
void ApplyBuiltInFunctions(Context* ctx);