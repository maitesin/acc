#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stdio.h>
#include "lexer.h"
#include "ast.h"
#include "token.h"

typedef struct grammar
{
	lexer * l;
} grammar;

void init_grammar(grammar * g, lexer * l);
ast_base * build_ast(grammar * g);
void destroy_grammar(grammar * g);


/*
 * Read functions to build AST parts
 */
ast_base * read_function_ast_node(grammar * g);
ast_base * read_body(grammar * g);
ast_base * read_return_expression(grammar * g);
ast_base * read_if_statement(grammar * g);
ast_base * read_boolean_expression(grammar * g);
ast_base * read_single_boolean_expression(grammar * g, ast_base * r,
					  int * op_found,
					  enum boolean_operator_type op);
ast_base * read_boolean_binary_expression(grammar * g);
ast_base * read_boolean_unary_expression(grammar * g);


#endif //GRAMMAR_H
