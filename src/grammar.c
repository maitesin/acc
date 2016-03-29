#include "grammar.h"
#include "lexer.h"
#include "ast.h"
#include "token.h"

void init_grammar(grammar * g, lexer * l)
{
	g->l = l;
}

void destroy_grammar(grammar * g)
{
	// Nothing to do, yet
}

ast_base * build_ast(grammar * g)
{
	return read_function_ast_node(g);
}

ast_base * read_function_ast_node(grammar * g)
{
	ast_base * root = NULL;
	ast_base * body = NULL;
	token_base * token = NULL;
	token_function * function_name = NULL;

	token = next(g->l);
	if (token->type != T_INT_TYPE)
	{
		return NULL;
	}
	free_token_int_type((token_int_type *)token);

	token = next(g->l);
	if (token->type != T_FUNCTION)
	{
		return NULL;
	}
	function_name = (token_function *) token;

	token = next(g->l);
	if (token->type != T_OPAR)
	{
		return NULL;
	}
	free_token_opar((token_opar *)token);

	token = next(g->l);
	if (token->type != T_CPAR)
	{
		return NULL;
	}
	free_token_cpar((token_cpar *)token);

	body = read_function_body(g);
	root = (ast_base *) malloc(sizeof(node_function));

	init_node_function((node_function *)root, function_name->name, body);
	free_token_function(function_name);
	return root;
}

ast_base * read_function_body(grammar * g)
{
	ast_base * root = NULL;
	token_base * token = NULL;

	token = next(g->l);
	if (token->type != T_OBRA)
	{
		return NULL;
	}
	free_token_obra((token_obra *)token);

	token = next(g->l);
	while (token->type != T_CBRA)
	{
		switch (token->type) {
			case T_RETURN:
				free_token_return((token_return *)token);
	            root = read_return_expression(g);
		        break;
			case T_IF:
				free_token_if((token_if *)token);
	            root = read_if_statement(g);
		        break;
			default:
				return NULL;
		}
		token = next(g->l);
    }
	free_token_cbra((token_cbra *)token);
	return root;
}

ast_base * read_return_expression(grammar * g)
{
	ast_base * root = NULL;
	ast_base * return_ast_value = NULL;
	token_base * token = NULL;
	token_int_value * int_value = NULL;

	token = next(g->l);
	if (token->type != T_INT_VALUE)
	{
		return NULL;
	}
	int_value = (token_int_value *) token;
	return_ast_value = (ast_base *) malloc(sizeof(node_int));
	init_node_int((node_int *)return_ast_value, int_value->value);
	free_token_int_value(int_value);

	root = (ast_base *) malloc(sizeof(node_return));
	init_node_return((node_return *)root, return_ast_value);

	token = next(g->l);
	if (token->type != T_SEMICOLON)
	{
		return NULL;
	}
	free_token_semicolon((token_semicolon *)token);

	return root;
}

ast_base * read_if_statement(grammar * g)
{
	ast_base * root = NULL;
	token_base * token = NULL;

	token = next(g->l);
	if (token->type != T_OPAR)
	{
		return NULL;
	}
	free_token_opar((token_opar *)token);

	root = read_boolean_expression(g);

	token = next(g->l);
	if (token->type != T_CPAR)
	{
		return NULL;
	}
	free_token_cpar((token_cpar *)token);

	return root;
}

ast_base * read_boolean_expression(grammar * g)
{
	ast_base * root = NULL;
	ast_base * tmp = NULL;
	ast_base * first = NULL;
	ast_base * second = NULL;
	token_base * token = NULL;
	enum boolean_operator_type op;
	int op_found = 0;

	root = (ast_base *) malloc(sizeof(node_boolean_operator));

	token = next(g->l);
	while (token->type != T_CPAR)
	{
		switch (token->type)
		{
			case T_INT_VALUE:
				push_back(g->l, token);
				tmp = read_boolean_binary_expression(g);
				if (root == NULL)
				{
					root = tmp;
				}
				else
				{
					if (op_found)
					{
						tmp = read_boolean_binary_expression(g);
						first = root;
						second = tmp;
						root = (ast_base *) malloc(sizeof(node_boolean_operator));
						init_node_boolean_operator((node_boolean_operator *)root, op, first, second);
						op_found = 0;
					}
					else
					{
						fprintf(stderr, "Error during read_boolean_expression with int value:%d\n", ((token_int_value *)token)->value);
						exit(EXIT_FAILURE);
					}
				}
				break;
			case T_BOOLEAN_OP:
				op = get_boolean_op_value((token_boolean_op *)token);
				op_found = 1;
				break;
		}
		token = next(g->l);
	}
	free_token_cpar((token_cpar *)token);
	return root;
}

ast_base * read_boolean_binary_expression(grammar * g)
{
	node_boolean_operator * root = NULL;
	ast_base * tmp = NULL;
	ast_base * first = NULL;
	ast_base * second = NULL;
	token_base * token = NULL;
	token_int_value * int_value = NULL;
	token_boolean_op * op = NULL;
	enum boolean_operator_type op_type;

	root = (node_boolean_operator *) malloc(sizeof(node_boolean_operator));

	token = next(g->l);
	if (token->type != T_INT_VALUE)
	{
		if (token->type == T_BOOLEAN_OP)
		{
			push_back(g->l, token);
			return read_boolean_unary_expression(g);
		}
		free_node_boolean_operator(root);
		return NULL;
	}
	int_value = (token_int_value *) token;
	tmp = (ast_base *) malloc(sizeof(node_int));
	init_node_int((node_int *)tmp, int_value->value);
	free_token_int_value(int_value);

	first = tmp;

	token = next(g->l);
	if (token->type != T_BOOLEAN_OP)
	{
		free_node_boolean_operator(root);
		return NULL;
	}
	op = (token_boolean_op *) token;
	op_type = get_boolean_op_value(op);
	free_token_boolean_op(op);

	token = next(g->l);
	if (token->type != T_INT_VALUE)
	{
		free_node_boolean_operator(root);
		return NULL;
	}
	int_value = (token_int_value *) token;
	tmp = (ast_base *) malloc(sizeof(node_int));
	init_node_int((node_int *)tmp, int_value->value);
	free_token_int_value(int_value);

	second = tmp;
	init_node_boolean_operator(root, op_type, first, second);
	return (ast_base *)root;
}

ast_base * read_boolean_unary_expression(grammar * g)
{
	node_boolean_operator * root = NULL;
	ast_base * tmp = NULL;
	ast_base * operand = NULL;
	token_base * token = NULL;
	token_int_value * int_value = NULL;
	token_boolean_op * op = NULL;
	enum boolean_operator_type op_type;

	root = (node_boolean_operator *) malloc(sizeof(node_boolean_operator));

	token = next(g->l);
	if (token->type != T_BOOLEAN_OP)
	{
		free_node_boolean_operator(root);
		return NULL;
	}
	op = (token_boolean_op *) token;
	op_type = get_boolean_op_value(op);
	free_token_boolean_op(op);

	token = next(g->l);
	if (token->type != T_INT_VALUE)
	{
		free_node_boolean_operator(root);
		return NULL;
	}
	int_value = (token_int_value *) token;
	tmp = (ast_base *) malloc(sizeof(node_int));
	init_node_int((node_int *)tmp, int_value->value);
	free_token_int_value(int_value);

	operand = tmp;
	init_node_boolean_operator(root, op_type, operand, NULL);
	return (ast_base *)root;
}
