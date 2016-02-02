#include "grammar.h"
#include "lexer.h"

void init_grammar(grammar * g, lexer * l)
{
	g->l = l;
}

void destroy_grammar(grammar * g)
{
	// Nothing to do, yet
}
