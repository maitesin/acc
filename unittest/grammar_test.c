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

TEST_F(GrammarTest, if_statement_only)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);
	char * op = (char *) malloc(sizeof(char)*3);
	op[0] = '!';
	op[1] = '=';
	op[2] = '\0';

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 9);
	base[0] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[0]);
	base[1] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[1], 1);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);
	base[3] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[3], op);
	base[4] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[4], 1);
	base[5] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[5]);
	base[6] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[6]);
	base[7] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[7]);
	base[8] = (token_base *) malloc(sizeof(token_eof));
	init_token_eof((token_eof *) base[8]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 9;

	// When
	ret = read_if_statement(&g);

	// Then
	assert(next_fake.call_count == 9);
	assert(ret != NULL);
	assert(ret->type == A_IF);
}

TEST_F(GrammarTest, if_else_statements)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);
	char * op = (char *) malloc(sizeof(char)*3);
	op[0] = '!';
	op[1] = '=';
	op[2] = '\0';

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 11);
	base[0] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[0]);
	base[1] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[1], 1);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);
	base[3] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[3], op);
	base[4] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[4], 1);
	base[5] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[5]);
	base[6] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[6]);
	base[7] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[7]);
	base[8] = (token_base *) malloc(sizeof(token_else));
	init_token_else((token_else *) base[8]);
	base[9] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[9]);
	base[10] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[10]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 11;

	// When
	ret = read_if_statement(&g);

	// Then
	assert(next_fake.call_count == 11);
	assert(ret != NULL);
	assert(ret->type == A_IF);

}

TEST_F(GrammarTest, body_with_two_returns)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 8);
	base[0] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[0]);
    base[1] = (token_base *) malloc(sizeof(token_return));
	init_token_return((token_return *) base[1]);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);
	base[3] = (token_base *) malloc(sizeof(token_semicolon));
	init_token_semicolon((token_semicolon *) base[3]);
	base[4] = (token_base *) malloc(sizeof(token_return));
	init_token_return((token_return *) base[4]);
	base[5] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[5], 1);
	base[6] = (token_base *) malloc(sizeof(token_semicolon));
	init_token_semicolon((token_semicolon *) base[6]);
	base[7] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[7]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 8;

	// When
	ret = read_body(&g);

	// Then
	assert(next_fake.call_count == 8);
	assert(ret != NULL);
	assert(ret->type == A_RETURN);
    assert(ret->next == A_RETURN);
    assert(ret->next->next == NULL);
}

TEST_F(GrammarTest, body_with_one_return)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 5);
	base[0] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[0]);
	base[1] = (token_base *) malloc(sizeof(token_return));
	init_token_return((token_return *) base[1]);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);
	base[3] = (token_base *) malloc(sizeof(token_semicolon));
	init_token_semicolon((token_semicolon *) base[3]);
	base[4] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[4]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 5;

	// When
	ret = read_body(&g);

	// Then
	assert(next_fake.call_count == 5);
	assert(ret != NULL);
	assert(ret->type == A_RETURN);
    assert(ret->next == NULL);
}

TEST_F(GrammarTest, if_statement_inside_if_statement)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);
	char * op1 = (char *) malloc(sizeof(char)*3);
    char * op2 = (char *) malloc(sizeof(char)*3);

	op1[0] = '!';
	op1[1] = '=';
	op1[2] = '\0';

    op2[0] = '!';
    op2[1] = '=';
    op2[2] = '\0';

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 18);
	base[0] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[0]);
	base[1] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[1], 1);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);
	base[3] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[3], op1);
	base[4] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[4], 1);
	base[5] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[5]);
	base[6] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[6]);

    base[7] = (token_base *) malloc(sizeof(token_if));
    init_token_if((token_if *) base[7]);
	base[8] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[8]);
	base[9] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[9], 1);
	base[10] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[10], 1);
	base[11] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[11], op2);
	base[12] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[12], 1);
	base[13] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[13]);
	base[14] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[14]);
	base[15] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[15]);

	base[16] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[16]);
	base[17] = (token_base *) malloc(sizeof(token_eof));
	init_token_eof((token_eof *) base[17]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 18;

	// When
	ret = read_if_statement(&g);

	// Then
	assert(next_fake.call_count == 18);
	assert(ret != NULL);
	assert(ret->type == A_IF);

}

TEST_F(GrammarTest, if_statement_inside_else_statement)
{
	lexer l;
	grammar g;
	token_base ** base;
	ast_base * ret = NULL;
	init_grammar(&g, &l);
	char * op1 = (char *) malloc(sizeof(char)*3);
    char * op2 = (char *) malloc(sizeof(char)*3);

	op1[0] = '!';
	op1[1] = '=';
	op1[2] = '\0';

    op2[0] = '!';
    op2[1] = '=';
    op2[2] = '\0';

	// Init stuff
	base = (token_base **) malloc(sizeof(token_base *) * 20);
	base[0] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[0]);
	base[1] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[1], 1);
	base[2] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[2], 1);
	base[3] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[3], op1);
	base[4] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[4], 1);
	base[5] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[5]);
	base[6] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[6]);
	base[7] = (token_base *) malloc(sizeof(token_else));
	init_token_else((token_else *) base[7]);
	base[8] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[8]);
	base[9] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[9]);
    base[10] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[10]);

    base[11] = (token_base *) malloc(sizeof(token_if));
    init_token_if((token_if *) base[11]);
	base[12] = (token_base *) malloc(sizeof(token_opar));
	init_token_opar((token_opar *) base[12]);
	base[13] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[13], 1);
	base[14] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[14], 1);
	base[15] = (token_base *) malloc(sizeof(token_boolean_op));
	init_token_boolean_op((token_boolean_op *) base[15], op2);
	base[16] = (token_base *) malloc(sizeof(token_int_value));
	init_token_int_value((token_int_value *) base[16], 1);
	base[17] = (token_base *) malloc(sizeof(token_cpar));
	init_token_cpar((token_cpar *) base[17]);
	base[18] = (token_base *) malloc(sizeof(token_obra));
	init_token_obra((token_obra *) base[18]);
	base[19] = (token_base *) malloc(sizeof(token_cbra));
	init_token_cbra((token_cbra *) base[19]);

	// Given
	next_fake.return_val_seq = base;
	next_fake.return_val_seq_len = 20;

	// When
	ret = read_if_statement(&g);

	// Then
	assert(next_fake.call_count == 20);
	assert(ret != NULL);
	assert(ret->type == A_IF);

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
	RUN_TEST(GrammarTest, if_statement_only);
	RUN_TEST(GrammarTest, if_else_statements);
    RUN_TEST(GrammarTest, if_statement_inside_if_statement);
    RUN_TEST(GrammarTest, if_statement_inside_else_statement);
    RUN_TEST(GrammarTest, body_with_one_return);
    RUN_TEST(GrammarTest, body_with_two_returns);

	printf("\n-------------\n");
	printf("Complete\n");
	printf("-------------\n\n");

	return 0;
}
