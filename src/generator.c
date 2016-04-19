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
	ast = build_ast(g->g);
	__generate_code(g, ast);
	free_node(ast);
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
    __generate_code_for_if_expression(g, ast->expression, if_num);
    // If body
    __generate_code_for_body(g, ast->i_body);
	fprintf(g->f, "if_else_%llu:\n", if_num);
    if (ast->e_body != NULL)
    {
        // Else body
        __generate_code_for_body(g, ast->e_body);
    }
}

void __generate_code_for_return(generator * g, node_return * ast)
{
	ast_base * return_value = ast->value;

	fprintf(g->f, "\tmov r0, ");
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
	fprintf(g->f, "\n\tbx lr\n");
}

void __generate_code_for_int(generator * g, node_int * ast)
{
	fprintf(g->f, "#%d", ast->value);
}

void __generate_code_for_if_expression(generator * g, ast_base * ast,
									   unsigned long long int if_num)
{
	struct node_boolean_operator * op = (struct node_boolean_operator *) ast;
	switch(op->oper)
	{
		case B_NOT:
			__generate_code_for_unary_boolean_expression(g, op, if_num);
			break;
		default:
			__generate_code_for_binary_boolean_expression(g, op, if_num);
	}
}

void __generate_code_for_binary_boolean_expression(generator * g,
											node_boolean_operator * op,
											unsigned long long int if_num)
{
	// Get both operands
	node_int * first = (node_int *) op->first;
	node_int * second = (node_int *) op->second;
	// Load first operand in r0
	fprintf(g->f, "\tmov r0, ");
	__generate_code_for_int(g, first);
	fprintf(g->f, "\n");
	// Load first operand in r1
	fprintf(g->f, "\tmov r1, ");
	__generate_code_for_int(g, second);
	fprintf(g->f, "\n");
	// Compare values
	fprintf(g->f, "\tcmp r0, r1\n");

	switch(op->oper)
		{
			case B_EQUALEQUAL:
				fprintf(g->f, "\tbne if_else_%llu\n", if_num);
				break;
			case B_NOTEQUAL:
				fprintf(g->f, "\tbeq if_else_%llu\n", if_num);
				break;
			case B_LTEQUAL:
				fprintf(g->f, "\tbgt if_else_%llu\n", if_num);
				break;
			case B_GTEQUAL:
				fprintf(g->f, "\tblt if_else_%llu\n", if_num);
				break;
			case B_OROR:
				// TODO
				break;
			case B_ANDAND:
				// TODO
				break;
			case B_LT:
				fprintf(g->f, "\tbge if_else_%llu\n", if_num);
				break;
			case B_GT:
				fprintf(g->f, "\tble if_else_%llu\n", if_num);
				break;
			default:
				fprintf(stderr, "Invalid unary boolean operator\n");
				exit(EXIT_FAILURE);
	}
}

void __generate_code_for_unary_boolean_expression(generator * g,
											node_boolean_operator * op,
											unsigned long long int if_num)
{
	node_int * first = (node_int *) op->first;
	fprintf(g->f, "\tmov r0, #0");
	fprintf(g->f, "\tmov r1, ");
	__generate_code_for_int(g, first);
	switch(op->oper)
	{
		case B_NOT:
			fprintf(g->f, "\tbeq if_else_%llu\n", if_num);
			break;
		default:
			fprintf(stderr, "Invalid unary boolean operator\n");
			exit(EXIT_FAILURE);
	}
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
			    break;
            case A_IF:
                __generate_code_for_if(g, (node_if *)tmp);
                break;
		    default:
			    //This is an error!
				fprintf(stderr, "Invalid stuff for the AST to have inside a function\n");
			    exit(EXIT_FAILURE);
	    }
    }
}
