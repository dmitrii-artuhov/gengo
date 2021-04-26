# CMakeList.txt: проект CMake для gengo; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (gengo "gengo.cpp" "gengo.h" "language/tokens/token.cpp" "language/tokens/token.h" "language/lexer/lexer.cpp" "language/lexer/lexer.h"  "utils/utils.cpp" "utils/utils.h" "language/error/error.cpp" "language/error/error.h" "language/run.cpp" "language/run.h" "language/tokens/position.cpp" "language/tokens/position.h" "language/nodes/ast.cpp" "language/nodes/ast.h" "language/parser/parser.h" "language/parser/parser.cpp" "language/interpreter/interpreter.h" "language/interpreter/interpreter.cpp" "language/symbol_table/symbol_table.cpp" "language/symbol_table/symbol_table.h" "language/context/context.cpp" "language/context/context.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
