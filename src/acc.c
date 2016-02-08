#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lexer.h"
#include "grammar.h"
#include "generator.h"


int main(int argc, char * argv[])
{
	// Parameters
	int debug_lexer = 0; // -l
	int debug_ast = 0; // -a
	char * filename = NULL;
	int c = 0;

	// Lexer, grammar and generator
	lexer lex;
	grammar gra;
	generator gen;

	// Parse parameters
	while ((c = getopt(argc, argv, "al:")) != -1)
	{
		switch(c)
		{
		case 'a':
			debug_ast = 1;
			break;
		case 'l':
			debug_lexer = 1;
			break;
		}
	}

	// Get file from parameters
	filename = argv[optind];

	// Initialize the lexer, the grammar and the generator
	init_lexer(&lex, filename);
	init_grammar(&gra, &lex);
	init_generator(&gen, &gra);
	// Do the magic stuff
	generate_code(&gen);
	// Release stuff adquired from the lexer, the grammar and the generator
	destroy_generator(&gen);
	destroy_grammar(&gra);
	destroy_lexer(&lex);
	return 0;
}
