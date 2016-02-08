#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "grammar.h"

typedef struct generator
{
	grammar * g;
} generator;

// API
void init_generator(generator * gen, grammar * gra);
void destroy_generator(generator * g);
void generate_code(generator * g);

// Internals
void __generate_code(ast_base * ast);
void __generate_code_for_main(ast_base * ast);
void __generate_code_for_function(ast_base * ast);
void __generate_code_for_return(ast_base * ast);
void __generate_code_for_int(ast_base * ast);

#endif //GENERATOR_H
