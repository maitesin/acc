#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "grammar.h"

typedef struct generator
{
	grammar * g;
} generator;

void init_generator(generator * gen, grammar * gra);
void destroy_generator(generator * g);
int generate_code(generator * g);

#endif //GENERATOR_H
