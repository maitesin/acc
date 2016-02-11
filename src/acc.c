#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lexer.h"
#include "grammar.h"
#include "generator.h"

int my_main(const char * file_input, const char * file_output)
{
	// Lexer, grammar and generator
	lexer lex;
	grammar gra;
	generator gen;

	// Initialize the lexer, the grammar and the generator
	init_lexer(&lex, file_input);
	init_grammar(&gra, &lex);
	init_generator(&gen, &gra, file_output);
	// Do the magic stuff
	generate_code(&gen);
	// Release stuff adquired from the lexer, the grammar and the generator
	destroy_generator(&gen);
	destroy_grammar(&gra);
	destroy_lexer(&lex);
	return 0;
}

int main(int argc, char * argv[])
{
	// Parameters
	char * file_output = NULL;
	int c = 0;

	// Parse parameters
	while ((c = getopt(argc, argv, "o:")) != -1)
	{
		switch(c)
		{
		case 'o':
			file_output = optarg;
			break;
		}
	}
	if (optind < argc)
	{
		return my_main(argv[optind], file_output == NULL ? "a.s" : file_output);
	} else
	{
		fprintf(stderr, "You need to provide a source file to compile\n");
		exit(EXIT_FAILURE);
	}
}
