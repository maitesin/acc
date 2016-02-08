#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "token.h"
#include "lexer.h"

void simple_file_only_main(void)
{
	const char * filename = "unittest/resources/simple_file_only_main.c";
	lexer l;
	token_base * token;

	// Initialize lexer
	init_lexer(&l, filename);

	/*
	 * Check that the tokens generated are the right ones
	 */
	token = next(&l); // int
	TEST_ASSERT_EQUAL(T_INT_TYPE, token->type);
	token = next(&l); // main
	TEST_ASSERT_EQUAL(T_FUNCTION, token->type);
	token = next(&l); // (
	TEST_ASSERT_EQUAL(T_OPAR, token->type);
	token = next(&l); // )
	TEST_ASSERT_EQUAL(T_CPAR, token->type);
	token = next(&l); // {
	TEST_ASSERT_EQUAL(T_OBRA, token->type);
	token = next(&l); // return
	TEST_ASSERT_EQUAL(T_RETURN, token->type);
	token = next(&l); // 2
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);
	token = next(&l); // ;
	TEST_ASSERT_EQUAL(T_SEMICOLON, token->type);
	token = next(&l); // }
	TEST_ASSERT_EQUAL(T_CBRA, token->type);
	token = next(&l); // END_OF_FILE
	TEST_ASSERT_EQUAL(T_END_OF_FILE, token->type);

	// Destroy lexer
	destroy_lexer(&l);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(simple_file_only_main);
	return UNITY_END();
}
