#include <stdio.h>
#include "generator.h"
#include "grammar.h"
#include "ast.h"

void init_generator(generator * gen, grammar * gra, const char * out)
{
	gen->g = gra;
	gen->f = fopen(out, "w");
}

void destroy_generator(generator * g)
{
	fclose(g->f);
}

void generate_code(generator * g)
{
	ast_base * ast = NULL;
	ast = read_function_ast_node(g->g);
	__generate_code(g, ast);
}

void __generate_code(generator * g, ast_base * ast)
{
	fprintf(g->f, "COMMON STUFF ON TOP\n");
	__generate_code_for_main(g, ast);
}

void __generate_code_for_main(generator * g, ast_base * ast)
{
	switch (ast->type)
	{
		case A_FUNCTION:
			__generate_code_for_function(g, (node_function *)ast);
			break;
		default:
			//This is an error!
			fprintf(stderr, "Invalid stuff for the AST to have in the main\n");
			exit(EXIT_FAILURE);
	}
}

void __generate_code_for_function(generator * g, node_function * ast)
{
	ast_base * body = ast->entry_point;

	fprintf(g->f, "%s:", "main");
	printf("%s\n", ast->name);
	switch(body->type)
	{
		case A_RETURN:
			__generate_code_for_return(g, (node_return *)body);
			break;
		default:
			//This is an error!
			fprintf(stderr, "Invalid stuff for the AST to have inside a function\n");
			exit(EXIT_FAILURE);
	}
}

void __generate_code_for_return(generator * g, node_return * ast)
{
	ast_base * return_value = ast->value;

	fprintf(g->f, "\tmv r0 ");
	switch(return_value->type)
	{
		case A_INT:
			__generate_code_for_int(g, (node_int *)return_value);
			break;
		default:
			//This is an error!
			fprintf(stderr, "Invalid value for a return statement\n");
			exit(EXIT_FAILURE);
	}
	fprintf(g->f, "\n");
}

void __generate_code_for_int(generator * g, node_int * ast)
{
	fprintf(g->f, "%d", ast->value);
}
