#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "token.h"
#include "lexer.h"

void simple_file_only_main(void)
{
	const char * filename = "unittest/resources/simple_file_only_main.c";
	struct lexer l;
	struct token_base * token;

	// Initialize lexer
	init_lexer(&l, filename);

	/*
	 * Check that the tokens generated are the right ones
	 */
	token = next(&l); // int
	TEST_ASSERT_EQUAL(INT_TYPE, token->type);
	token = next(&l); // main
	TEST_ASSERT_EQUAL(FUNCTION, token->type);
	token = next(&l); // (
	TEST_ASSERT_EQUAL(OPAR, token->type);
	token = next(&l); // )
	TEST_ASSERT_EQUAL(CPAR, token->type);
	token = next(&l); // {
	TEST_ASSERT_EQUAL(OBRA, token->type);
	token = next(&l); // return
	TEST_ASSERT_EQUAL(RETURN, token->type);
	token = next(&l); // 2
	TEST_ASSERT_EQUAL(INT_VALUE, token->type);
	token = next(&l); // ;
	TEST_ASSERT_EQUAL(SEMICOLON, token->type);
	token = next(&l); // }
	TEST_ASSERT_EQUAL(CBRA, token->type);
	token = next(&l); // END_OF_FILE
	TEST_ASSERT_EQUAL(END_OF_FILE, token->type);

	// Destroy lexer
	destroy_lexer(&l);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(simple_file_only_main);
	return UNITY_END();
}
