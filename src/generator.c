#include <stdio.h>
#include "generator.h"
#include "grammar.h"
#include "ast.h"

void init_generator(generator * gen, grammar * gra)
{
	gen->g = gra;
}

void destroy_generator(generator * g)
{
	// Nothing to do, yet
}

void generate_code(generator * g)
{
	ast_base * ast = NULL;
	ast = read_function_ast_node(g->g);
	__generate_code(ast);
}

void __generate_code(ast_base * ast)
{
	fprintf(stdout, "COMMON STUFF ON TOP\n");
	__generate_code_for_main(ast);
}

void __generate_code_for_main(ast_base * ast)
{
	if (ast->type != A_FUNCTION)
	{
		fprintf(stderr, "FUNCTION for the AST is not in the right place\n");
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "main:");
	__generate_code_for_function(ast);
}

void __generate_code_for_function(ast_base * ast)
{
	node_function * function = (node_function *) ast;
	ast_base * body = function->entry_point;

	switch(body->type)
	{
		case A_RETURN:
			__generate_code_for_return(body);
			break;
		default:
			//This is an error!
			fprintf(stderr, "Invalid stuff for the AST to have inside a function\n");
			exit(EXIT_FAILURE);
	}
}

void __generate_code_for_return(ast_base * ast)
{
	ast_base * return_value = NULL;
	node_return * return_ast = NULL;

	if (ast->type != A_RETURN)
	{
		fprintf(stderr, "RETURN for the AST is not in the right place");
		exit(EXIT_FAILURE);
	}
	return_ast = (node_return *) ast;
	return_value = return_ast->value;

	fprintf(stdout, "\tmv r0 ");
	switch(return_value->type)
	{
		case A_INT:
			__generate_code_for_int(return_value);
			break;
		default:
			fprintf(stderr, "Invalid value for a return statement\n");
			exit(EXIT_FAILURE);
	}
	fprintf(stdout, "\n");
}

void __generate_code_for_int(ast_base * ast)
{
	node_int * node = NULL;
	if (ast->type != A_INT)
	{
		fprintf(stderr, "INT for the AST is not in the right place");
		exit(EXIT_FAILURE);
	}
	node = (node_int *) ast;
	fprintf(stdout, "%d", node->value);
}
