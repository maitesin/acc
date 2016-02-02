project(ACC)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(inc/unity)
ADD_EXECUTABLE(lexer_tests unittest/lexer_test.c inc/unity/unity.c src/token.c src/lexer.c)
