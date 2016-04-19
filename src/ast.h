#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "token.h"

// AST TYPES
enum ast_type {
	A_ID,
	A_INT,
	A_FUNCTION,
	A_RETURN,
	A_IF,
	A_BOOLEAN_OPERATOR
};

// Boolean operators
enum boolean_operator_type {
	B_EQUALEQUAL,
	B_NOTEQUAL,
	B_LTEQUAL,
	B_GTEQUAL,
	B_OROR,
	B_ANDAND,
	B_LT,
	B_GT,
	B_NOT
};

/*
 * AST nodes
 */
typedef struct ast_base
{
	enum ast_type type;
	struct ast_base * next;
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
	ast_base * entry_point;
} node_function;

typedef struct node_return
{
	ast_base base;
	ast_base * value;
} node_return;

typedef struct node_if
{
	ast_base base;
	ast_base * expression;
	ast_base * i_body;
	ast_base * e_body;
} node_if;

typedef struct node_boolean_operator
{
	ast_base base;
	ast_base * first;
	ast_base * second;
	enum boolean_operator_type oper;
} node_boolean_operator;

/*
 * Init functions for the AST nodes
 */
void init_ast_base(ast_base * base, enum ast_type type, ast_base * next);
void init_ast_base_single(ast_base * base, enum ast_type type);
void init_node_id(node_id * node, char * value);
void init_node_int(node_int * node, int value);
void init_node_function(node_function * node, char * name,
			ast_base * entry_point);
void init_node_return(node_return * node, ast_base * value);
void init_node_if(node_if * node, ast_base * expression, ast_base * i_body,
		  ast_base * e_body);
void init_node_boolean_operator(node_boolean_operator * node,
				enum boolean_operator_type type,
				ast_base * first, ast_base * second);

/*
 * Release functions for the AST nodes
 */
void free_node(ast_base *);
void free_node_id(node_id * node);
void free_node_int(node_int * node);
void free_node_function(node_function * node);
void free_node_return(node_return * node);
void free_node_if(node_if * node);
void free_node_boolean_operator(node_boolean_operator * node);

/*
 * Auxiliar functions
 */
enum boolean_operator_type get_boolean_op_value(token_boolean_op * token);
#endif //AST_H
