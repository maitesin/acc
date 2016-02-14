project(ACC)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(inc/unity)
INCLUDE_DIRECTORIES(inc/fff)

# Test for the lexer
ADD_EXECUTABLE(lexer_tests unittest/lexer_test.c inc/unity/unity.c src/token.c src/lexer.c)
ADD_TEST(NAME lexer_tests COMMAND ./bin/lexer_tests)

# Test for the grammar
ADD_EXECUTABLE(grammar_tests unittest/grammar_test.c src/token.c src/ast.c src/grammar.c)
ADD_TEST(NAME grammar_tests COMMAND ./bin/grammar_tests)

# Executable of ARM C Compiler
ADD_EXECUTABLE(acc src/acc.c src/token.c src/lexer.c src/ast.c src/grammar.c src/generator.c)

