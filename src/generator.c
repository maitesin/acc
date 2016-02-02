#include <stdio.h>
#include "generator.h"
#include "grammar.h"

void init_generator(generator * gen, grammar * gra)
{
	gen->g = gra;
}

void destroy_generator(generator * g)
{
	// Nothing to do, yet
}

int generate_code(generator * g)
{
	// Insert magic here
	return 0;
}
