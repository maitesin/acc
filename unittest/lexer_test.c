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

void if_without_else(void)
{
	char * code = "int main()\
	{\
		if (1 == 1)\
		{\
			return 2;\
		}\
		return 3;\
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
	token = next(&l); // if
	TEST_ASSERT_EQUAL(T_IF, token->type);
	token = next(&l); // (
	TEST_ASSERT_EQUAL(T_OPAR, token->type);
	token = next(&l); // 1
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);
	token = next(&l); // ==
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);
	token = next(&l); // 1
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);
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
	token = next(&l); // return
	TEST_ASSERT_EQUAL(T_RETURN, token->type);
	token = next(&l); // 3
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

void if_with_else(void)
{
	char * code = "int main()\
	{\
		if (1 == 1)\
		{\
			return 2;\
		}\
		else\
		{\
			return 4;\
		}\
		return 3;\
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
	token = next(&l); // if
	TEST_ASSERT_EQUAL(T_IF, token->type);
	token = next(&l); // (
	TEST_ASSERT_EQUAL(T_OPAR, token->type);
	token = next(&l); // 1
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);
	token = next(&l); // ==
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);
	token = next(&l); // 1
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);
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
	token = next(&l); // else
	TEST_ASSERT_EQUAL(T_ELSE, token->type);
	token = next(&l); // {
	TEST_ASSERT_EQUAL(T_OBRA, token->type);
	token = next(&l); // return
	TEST_ASSERT_EQUAL(T_RETURN, token->type);
	token = next(&l); // 4
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);
	token = next(&l); // ;
	TEST_ASSERT_EQUAL(T_SEMICOLON, token->type);
	token = next(&l); // }
	TEST_ASSERT_EQUAL(T_CBRA, token->type);
	token = next(&l); // return
	TEST_ASSERT_EQUAL(T_RETURN, token->type);
	token = next(&l); // 3
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

void read_token_int_type(void)
{
	char * code = "int";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_INT_TYPE, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_int_value(void)
{
	char * code = "1234";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_INT_VALUE, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_function(void)
{
	char * code = "main";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_FUNCTION, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_opar(void)
{
	char * code = "(";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_OPAR, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_cpar(void)
{
	char * code = ")";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_CPAR, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_obra(void)
{
	char * code = "{";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_OBRA, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_cbra(void)
{
	char * code = "}";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_CBRA, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_return(void)
{
	char * code = "return";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_RETURN, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_semicolon(void)
{
	char * code = ";";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_SEMICOLON, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_eof(void)
{
	char * code = "";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_END_OF_FILE, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}


void read_token_if(void)
{
	char * code = "if";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_IF, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_else(void)
{
	char * code = "else";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_ELSE, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_equalequal(void)
{
	char * code = "==";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_notequal(void)
{
	char * code = "!=";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_lessequalthan(void)
{
	char * code = "<=";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_greaterequalthan(void)
{
	char * code = ">=";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_lessthan(void)
{
	char * code = "<";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_greaterthan(void)
{
	char * code = ">";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

void read_token_not(void)
{
	char * code = "!";
	lexer l;
	token_base * token;

	// Init stuff
	init_lexer(&l, code);

	// Check the stuff
	token = next(&l);
	TEST_ASSERT_EQUAL(T_BOOLEAN_OP, token->type);

	// Destroy stuff
	destroy_lexer(&l);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(simple_file_only_main);
	RUN_TEST(push_token_to_stack);
	RUN_TEST(push_two_tokens_to_stack);
	RUN_TEST(push_token_and_call_next);
	RUN_TEST(if_without_else);
	RUN_TEST(if_with_else);
	RUN_TEST(read_token_int_type);
	RUN_TEST(read_token_int_value);
	RUN_TEST(read_token_function);
	RUN_TEST(read_token_opar);
	RUN_TEST(read_token_cpar);
	RUN_TEST(read_token_obra);
	RUN_TEST(read_token_cbra);
	RUN_TEST(read_token_return);
	RUN_TEST(read_token_semicolon);
	RUN_TEST(read_token_eof);
	RUN_TEST(read_token_if);
	RUN_TEST(read_token_else);
	RUN_TEST(read_token_equalequal);
	RUN_TEST(read_token_notequal);
	RUN_TEST(read_token_lessequalthan);
	RUN_TEST(read_token_greaterequalthan);
	RUN_TEST(read_token_lessthan);
	RUN_TEST(read_token_greaterthan);
	RUN_TEST(read_token_not);
	return UNITY_END();
}
