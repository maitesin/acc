#include <stdio.h>
#include <stdlib.h>
#include "unity.h"
#include "token.h"
#include "lexer.h"

void simple_file_only_main(void)
{
	char * code = "int main()\
	{\
		return 2;\
	}";
	lexer l;
	token_base * token;

	// Initialize lexer
	init_lexer(&l, code);

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

void push_token_to_stack(void)
{
	char * code = "int main()\
	{\
		return 2;\
	}";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);
	token = (token_base *) malloc(sizeof(token_int_value));

	// Check the stuff
	push_back(&l, token);
	TEST_ASSERT_EQUAL(l.stack->token, token);

	// Destroy stuff
	destroy_lexer(&l);
	free(token);
}

void push_two_tokens_to_stack(void)
{
	char * code = "int main()\
	{\
		return 2;\
	}";
	lexer l;
	token_base * token1;
	token_base * token2;

	// Init stuff
	init_lexer(&l, code);
	token1 = (token_base *) malloc(sizeof(token_int_value));
	token2 = (token_base *) malloc(sizeof(token_int_value));

	// Check the stuff
	push_back(&l, token1);
	TEST_ASSERT_EQUAL(l.stack->token, token1);
	push_back(&l, token2);
	TEST_ASSERT_EQUAL(l.stack->token, token2);

	// Destroy stuff
	destroy_lexer(&l);
	free(token1);
	free(token2);
}

void push_token_and_call_next(void)
{
	char * code = "int main()\
	{\
		return 2;\
	}";
	lexer l;
	token_base * token;
	token_base * received;

	// Init stuff
	init_lexer(&l, code);
	token = (token_base *) malloc(sizeof(token_int_value));

	// Check the stuff
	push_back(&l, token);
	received = next(&l);
	TEST_ASSERT_EQUAL(token, received);

	// Destroy stuff
	destroy_lexer(&l);
	free(token);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(simple_file_only_main);
	RUN_TEST(push_token_to_stack);
	RUN_TEST(push_two_tokens_to_stack);
	RUN_TEST(push_token_and_call_next);
	return UNITY_END();
}
