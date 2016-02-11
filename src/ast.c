#include "ast.h"

/*
 * Init functions implementation
 */
void init_node_id(node_id * node, char * value)
{
	node->base.type = A_ID;
	node->base.ast_pointer = node;
	node->value = value;
}

void init_node_int(node_int * node, int value)
{
	node->base.type = A_INT;
	node->base.ast_pointer = node;
	node->value = value;
}

void init_node_function(node_function * node, char * name, ast_base * entry)
{
	node->base.type = A_FUNCTION;
	node->base.ast_pointer = node;
	node->name = name;
	node->entry_point = entry;
}

void init_node_return(node_return * node, ast_base * value)
{
	node->base.type = A_RETURN;
	node->base.ast_pointer = node;
	node->value = value;
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
