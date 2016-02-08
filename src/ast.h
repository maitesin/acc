#ifndef AST_H
#define AST_H

#include <stdlib.h>

enum ast_type {
	A_ID,
	A_INT,
	A_FUNCTION,
	A_RETURN
};

/*
 * AST nodes
 */
typedef struct ast_base
{
	enum ast_type type;
	void * ast_pointer;
} ast_base;

typedef struct node_id
{
	ast_base base;
	const char * value;
} node_id;

typedef struct node_int
{
	ast_base base;
	int value;
} node_int;

typedef struct node_function
{
	ast_base base;
	const char * name;
	ast_base * entry_point;
} node_function;

typedef struct node_return
{
	ast_base base;
	ast_base * value;
} node_return;

/*
 * Init functions for the AST nodes
 */
void init_node_id(node_id * node, const char * value);
void init_node_int(node_int * node, const int value);
void init_node_function(node_function * node, const char * name, ast_base * entry_point);
void init_node_return(node_return * node, ast_base * value);

#endif //AST_H
