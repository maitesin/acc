#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stdio.h>
#include "lexer.h"
#include "ast.h"

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
ast_base * read_function_body(grammar * g);
#endif //GRAMMAR_H
