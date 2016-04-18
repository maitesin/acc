#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "grammar.h"

typedef struct generator
{
	grammar * g;
	FILE * f;
        unsigned long long if_num;
} generator;

// API
void init_generator(generator * gen, grammar * gra, const char * out);
void destroy_generator(generator * g);
void generate_code(generator * g);

// Internals
void __generate_code(generator * g, ast_base * ast);
void __generate_code_for_main(generator * g, ast_base * ast);
void __generate_code_for_function(generator * g, node_function * ast);
void __generate_code_for_return(generator * g, node_return * ast);
void __generate_code_for_int(generator * g, node_int * ast);
void __generate_code_for_if(generator * g, node_if * ast);
void __generate_code_for_expression(generator * g, ast_base * ast);
void __generate_code_for_body(generator * g, ast_base * body);

#endif //GENERATOR_H
