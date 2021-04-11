# CMakeList.txt: проект CMake для gengo; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
add_executable (gengo "gengo.cpp" "gengo.h" "language/token.cpp" "headers/token.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
