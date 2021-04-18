# CMakeList.txt: проект CMake для gengo; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (gengo "gengo.cpp" "gengo.h" "language/token.cpp" "headers/token.h" "language/lexer.cpp" "headers/lexer.h"  "utils/utils.cpp" "utils/utils.h" "language/error.cpp" "headers/error.h" "language/run.cpp" "headers/run.h" "language/position.cpp" "headers/position.h" "language/ast.cpp" "headers/ast.h" "headers/parser.h" "language/parser.cpp" "headers/interpreter.h" "language/interpreter.cpp")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
