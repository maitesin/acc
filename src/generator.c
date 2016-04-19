#include <stdio.h>
#include "generator.h"
#include "grammar.h"
#include "ast.h"

void init_generator(generator * gen, grammar * gra, const char * out)
{
	gen->g = gra;
	gen->f = fopen(out, "w");
    gen->if_num = 0LLU;
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
	fprintf(g->f, "\t.text\n\t.global main\n");
	__generate_code_for_main(g, ast);
}

void __generate_code_for_main(generator * g, ast_base * ast)
{
	switch (ast->type)
	{
		case A_FUNCTION:
			__generate_code_for_function(g, (node_function *)ast);
			free_node_function((node_function *)ast);
			break;
		default:
			//This is an error!
			fprintf(stderr, "Invalid stuff for the AST to have in the main\n");
			exit(EXIT_FAILURE);
	}
}

void __generate_code_for_function(generator * g, node_function * ast)
{
	fprintf(g->f, "%s:\n", ast->name);
    __generate_code_for_body(g, ast->entry_point);
}

void __generate_code_for_if(generator * g, node_if * ast)
{
    unsigned long long int if_num = g->if_num;
    g->if_num++;
    // Expression
    __generate_code_for_expression(g, ast->expression);
    // If body
    fprintf(g->f, "if_if_%llu:\n", if_num);
    __generate_code_for_body(g, ast->i_body);
    if (ast->e_body != NULL)
    {
        // Else body
        fprintf(g->f, "if_else_%llu:\n", if_num);
        __generate_code_for_body(g, ast->e_body);
    }
    // End of if_else
    fprintf(g->f, "if_end_%llu:\n", g->if_num);
}

void __generate_code_for_return(generator * g, node_return * ast)
{
	ast_base * return_value = ast->value;

	fprintf(g->f, "\tmov r0, ");
	switch(return_value->type)
	{
		case A_INT:
			__generate_code_for_int(g, (node_int *)return_value);
			free_node_int((node_int *)return_value);
			break;
		default:
			//This is an error!
			fprintf(stderr, "Invalid value for a return statement\n");
			exit(EXIT_FAILURE);
	}
	fprintf(g->f, "\n\tbx lr\n");
}

void __generate_code_for_int(generator * g, node_int * ast)
{
	fprintf(g->f, "#%d", ast->value);
}

void __generate_code_for_expression(generator * g, ast_base * ast)
{

}

void __generate_code_for_body(generator * g, ast_base * body)
{
	ast_base * tmp = NULL;
    while (body != NULL)
    {
        tmp = body;
        body = body->next;
	    switch(tmp->type)
    	{
    	    case A_RETURN:
	    	    __generate_code_for_return(g, (node_return *)tmp);
                free_node_return((node_return *)tmp);
    		    break;
            case A_IF:
                __generate_code_for_if(g, (node_if *)tmp);
                free_node_if((node_if *)tmp);
                break;
    	    default:
	    	    //This is an error!
		    	fprintf(stderr, "Invalid stuff for the AST to have inside a function\n");
    		    exit(EXIT_FAILURE);
	    }
    }
}
