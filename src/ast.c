#include <stdio.h>
#include "ast.h"

/*
 * Init functions implementation
 */
void init_ast_base(ast_base * base, enum ast_type type, ast_base * next)
{
	base->type = type;
	base->next = next;
}

void init_ast_base_single(ast_base * base, enum ast_type type)
{
	init_ast_base(base, type, NULL);
}

void init_node_id(node_id * node, char * value)
{
	init_ast_base_single(&node->base, A_ID);
	node->value = value;
}

void init_node_int(node_int * node, int value)
{

	init_ast_base_single(&node->base, A_INT);
	node->value = value;
}

void init_node_function(node_function * node, char * name, ast_base * entry)
{
	init_ast_base_single(&node->base, A_FUNCTION);
	node->name = name;
	node->entry_point = entry;
}

void init_node_return(node_return * node, ast_base * value)
{
	init_ast_base_single(&node->base, A_RETURN);
	node->value = value;
}

void init_node_if(node_if * node, ast_base * expression, ast_base * i_body,
				  ast_base * e_body)
{
	init_ast_base_single(&node->base, A_IF);
	node->expression = expression;
	node->i_body = i_body;
	node->e_body = e_body;
}

void init_node_boolean_operator(node_boolean_operator * node, enum boolean_operator_type
			   type, ast_base * first, ast_base * second)
{
	init_ast_base_single(&node->base, A_ID);
	node->base.type = A_BOOLEAN_OPERATOR;
	node->oper = type;
	node->first = first;
	node->second = second;
}

/*
 * Release functions implementation
 */
void free_node(ast_base * base)
{
	switch(base->type)
	{
	case A_ID:
		free_node_id((node_id *)base);
		break;
	case A_INT:
		free_node_int((node_int *)base);
		break;
	case A_FUNCTION:
		free_node_function((node_function *)base);
		break;
	case A_RETURN:
		free_node_return((node_return *)base);
		break;
	case A_IF:
		free_node_if((node_if *)base);
		break;
	case A_BOOLEAN_OPERATOR:
		free_node_boolean_operator((node_boolean_operator *)base);
		break;
	default:
		fprintf(stderr, "Error, unable to free ast_base\n");
		exit(EXIT_FAILURE);
	}
}
void free_node_id(node_id * node)
{
	if (node->base.next != NULL) {
		free_node(node->base.next);
	}
	free(node);
}
void free_node_int(node_int * node)
{
	if (node->base.next != NULL) {
		free_node(node->base.next);
	}
	free(node);
}
void free_node_function(node_function * node)
{
	if (node->base.next != NULL) {
		free_node(node->base.next);
	}
	free(node->name);
	free(node);
}
void free_node_return(node_return * node)
{
	if (node->base.next != NULL) {
		free_node(node->base.next);
	}
	free(node);
}
void free_node_if(node_if * node)
{
	if (node->base.next != NULL) {
		free_node(node->base.next);
	}
	free_node(node->expression);
	free_node(node->i_body);
	free_node(node->e_body);
	free(node);
}
void free_node_boolean_operator(node_boolean_operator * node)
{
	if (node->base.next != NULL) {
		free_node(node->base.next);
	}
	free_node(node->first);
	free_node(node->second);
	free(node);
}

enum boolean_operator_type get_boolean_op_value(token_boolean_op * token)
{
	size_t len = strnlen(token->op,2);
	if (len == 2)
	{
		if (strncmp(token->op, "==", 2) == 0)
			return B_EQUALEQUAL;
		else if (strncmp(token->op, "!=", 2) == 0)
			return B_NOTEQUAL;
		else if (strncmp(token->op, "<=", 2) == 0)
			return B_LTEQUAL;
		else if (strncmp(token->op, ">=", 2) == 0)
			return B_GTEQUAL;
		else
		{
			fprintf(stderr, "Error, %s cannot be proccessed as a boolean operator\n", token->op);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		switch(token->op[0])
		{
			case '!':
				return B_NOT;
			case '<':
				return B_LT;
			case '>':
				return B_GT;
			default:
				fprintf(stderr, "Error, %s cannot be proccessed as a boolean operator\n", token->op);
				exit(EXIT_FAILURE);
		}
	}
}

