#ifndef AST_H
#define AST_H

#include <stdlib.h>

enum ast_type {
	ID,
	INT,
	FUNCTION
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
	char * value;
} node_id;

typedef struct node_int
{
	ast_base base;
	int value;
} node_int;

typedef struct node_function
{
	ast_base base;
	char * name;
} node_function;

/*
 * Init functions for the AST nodes
 */
void init_node_id(node_id * node, char * value);
void init_node_int(node_int * node, int value);
void init_node_function(node_function * node, char * name);

#endif //AST_H
