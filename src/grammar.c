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
	ast_base * return_ast_value = NULL;
	token_base * token = NULL;
	token_int_value * int_value = NULL;

	token = next(g->l);
	if (token->type != T_OBRA)
	{
		return NULL;
	}
	free_token_obra((token_obra *)token);

	token = next(g->l);
	if (token->type != T_RETURN)
	{
		return NULL;
	}
	free_token_return((token_return *)token);

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

	token = next(g->l);
	if (token->type != T_CBRA)
	{
		return NULL;
	}
	free_token_cbra((token_cbra *)token);
	return root;
}
