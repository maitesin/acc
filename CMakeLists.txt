project(ACC)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(inc/unity)

# Test for the lexer
ADD_EXECUTABLE(lexer_tests unittest/lexer_test.c inc/unity/unity.c src/token.c src/lexer.c)
ADD_TEST(NAME lexer_tests COMMAND ./bin/lexer_tests)

# Executable of ARM C Compiler
ADD_EXECUTABLE(acc src/acc.c src/token.c src/lexer.c src/ast.c src/grammar.c src/generator.c)

