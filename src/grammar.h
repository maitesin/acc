#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <stdio.h>
#include "lexer.h"

typedef struct grammar
{
	lexer * l;
} grammar;

void init_grammar(grammar * g, lexer * l);
void destroy_grammar(grammar * g);

#endif //GRAMMAR_H
