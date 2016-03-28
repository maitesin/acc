#include "ast.h"

/*
 * Init functions implementation
 */
void init_node_id(node_id * node, char * value)
{
	node->base.type = A_ID;
	node->value = value;
}

void init_node_int(node_int * node, int value)
{
	node->base.type = A_INT;
	node->value = value;
}

void init_node_function(node_function * node, char * name, ast_base * entry)
{
	node->base.type = A_FUNCTION;
	node->name = name;
	node->entry_point = entry;
}

void init_node_return(node_return * node, ast_base * value)
{
	node->base.type = A_RETURN;
	node->value = value;
}

void init_node_if(node_if * node, ast_base * expression)
{
	node->base.type = A_IF;
	node->expression = expression;
}

void init_node_boolean_operator(node_boolean_operator * node, enum boolean_operator_type
			   type, ast_base * first, ast_base * second)
{
	node->base.type = A_BOOLEAN_OPERATOR;
	node->oper = type;
	node->first = first;
	node->second = second;
}

/*
 * Release functions implementation
 */
void free_node_id(node_id * node)
{
	free(node);
}
void free_node_int(node_int * node)
{
	free(node);
}
void free_node_function(node_function * node)
{
	free(node->name);
	free(node);
}
void free_node_return(node_return * node)
{
	free(node);
}

enum boolean_operator_type set_node_boolean_op_value(token_boolean_op * token)
{
	size_t len = strnlen(token->op,2);
	if (len == 2)
	{
		if (strncmp(token->op, "==", 2))
			return B_EQUALEQUAL;
		else if (strncmp(token->op, "!=", 2))
			return B_NOTEQUAL;
		else if (strncmp(token->op, "<=", 2))
			return B_LTEQUAL;
		else if (strncmp(token->op, ">=", 2))
			return B_GTEQUAL;
		else
		{
			fprintf(stderr, "Error, %s cannot be proccessed as a boolean operator\n", token->op);
			exit(-1);

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
				exit(-1);
		}
	}
}

