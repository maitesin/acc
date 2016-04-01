#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "token.h"
#include "lexer.h"
#include "grammar.h"
// Needed stuff to do mocks
#include "fff.h"
DEFINE_FFF_GLOBALS;
#define TEST_F(SUITE, NAME) void NAME()
#define RUN_TEST(SUITE, TESTNAME) printf(" Running %s.%s: \n", #SUITE, #TESTNAME); setup(); TESTNAME(); printf(" SUCCESS\n");

FAKE_VALUE_FUNC1(token_base *, next, lexer *);
FAKE_VOID_FUNC2(push_back, lexer *, token_base *);

void setup()
{
	RESET_FAKE(next);
	RESET_FAKE(push_back);
}

TEST_F(GrammarTest, no_int_as_first_stuff)
{
	lexer l;
	grammar g;
	init_grammar(&g, &l);
	ast_base * ret = NULL;

	// Given
	token_base * base = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base);
	next_fake.return_val = base;

	// When
	ret = read_function_ast_node(&g);

	// Then
	assert(next_fake.call_count == 1);
	assert(ret == NULL);
}

TEST_F(GrammarTest, int_but_not_followed_by_function)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 2);
	base[0] = (token_base *) malloc(sizeof(token_int_type));
	init_token_int_type((token_int_type *) base[0]);
	base[1] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[1]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 2;

	// When
	ret = read_function_ast_node(&g);

	// Then
	assert(next_fake.call_count == 2);
	assert(ret == NULL);
}

TEST_F(GrammarTest, boolean_expression_is_read_properly)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	node_boolean_operator * node = NULL;
	char * op = (char *) malloc(sizeof(char)*3);
	op[0] = '!';
	op[1] = '=';
	op[2] = '\0';

	init_grammar(&g, &l);

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 5);
	base[0] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[0], 2);
	base[1] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[1], 2);
	base[2] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[2], op);
	base[3] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[3], 1);
	base[4] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[4]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 5;

	// When
	ret = read_boolean_expression(&g);

	// Then
	assert(next_fake.call_count == 5);
	assert(push_back_fake.call_count == 1);
	assert(ret->type == A_BOOLEAN_OPERATOR);
}

TEST_F(GrammarTest, boolean_binary_operator_is_read_properly)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	node_boolean_operator * node = NULL;
	char * op = (char *) malloc(sizeof(char)*3);
	op[0] = '!';
	op[1] = '=';
	op[2] = '\0';

	init_grammar(&g, &l);

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 3);
	base[0] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[0], 2);
	base[1] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[1], op);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 3;

	// When
	ret = read_boolean_binary_expression(&g);

	// Then
	assert(next_fake.call_count == 3);
	assert(ret->type == A_BOOLEAN_OPERATOR);
	node = (node_boolean_operator *)ret;
	assert(node->first->type == A_INT);
	assert(node->oper == B_NOTEQUAL);
	assert(node->second->type == A_INT);
}

TEST_F(GrammarTest, boolean_unary_operator_is_read_properly)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	node_boolean_operator * node = NULL;
	char * op = (char *) malloc(sizeof(char)*2);
	op[0] = '!';
	op[1] = '\0';

	init_grammar(&g, &l);

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 2);
	base[0] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[0], op);
	base[1] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[1], 1);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 2;

	// When
	ret = read_boolean_unary_expression(&g);

	// Then
	assert(next_fake.call_count == 2);
	assert(ret->type == A_BOOLEAN_OPERATOR);
	node = (node_boolean_operator *)ret;
	assert(node->first->type == A_INT);
	assert(node->oper == B_NOT);
	assert(node->second == NULL);
}

int main()
{
	setbuf(stdout, NULL);
	fprintf(stdout, "-------------\n");
	fprintf(stdout, "Running Tests\n");
	fprintf(stdout, "-------------\n\n");
    fflush(0);

	RUN_TEST(GrammarTest, no_int_as_first_stuff);
	RUN_TEST(GrammarTest, int_but_not_followed_by_function);
	RUN_TEST(GrammarTest, boolean_unary_operator_is_read_properly);
	RUN_TEST(GrammarTest, boolean_binary_operator_is_read_properly);
	RUN_TEST(GrammarTest, boolean_expression_is_read_properly);

	printf("\n-------------\n");
    printf("Complete\n");
	printf("-------------\n\n");

	return 0;
}
