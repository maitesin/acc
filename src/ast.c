#include "ast.h"

void init_node_id(node_id * node, char * value)
{
	node->base.type = ID;
	node->base.ast_pointer = node;
	node->value = value;
}

void init_node_int(node_int * node, int value)
{
	node->base.type = INT;
	node->base.ast_pointer = node;
	node->value = value;
}

void init_node_function(node_function * node, char * name)
{
	node->base.type = FUNCTION;
	node->base.ast_pointer = node;
	node->name = name;

}

