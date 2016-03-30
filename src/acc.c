#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "lexer.h"
#include "grammar.h"
#include "generator.h"

char * load_file(const char * filename)
{
	char * b = NULL;
	FILE * f = fopen(filename, "r");
	long s;
	size_t real_len;
	if (f != NULL)
	{
		if (fseek(f, 0L, SEEK_END) == 0)
		{
			s = ftell(f);
			if (s == -1)
			{
				fprintf(stderr, "Error, not able to calculate the size of the file \n");
				exit(EXIT_FAILURE);
			}
			b = (char *) malloc(sizeof(char) * s);
			if (fseek(f, 0L, SEEK_SET) != 0)
			{
				fprintf(stderr, "Error, not got back to the beginning of the file\n");
				exit(EXIT_FAILURE);
			}
			real_len = fread(b, sizeof(char), s, f);
			if (real_len == 0)
			{
				fprintf(stderr, "Error, reading file %s\n", filename);
				exit(EXIT_FAILURE);
			}
			b[real_len] = '\0';
		}
		fclose(f);
	}
	return b;
}

int my_main(const char * file_input, const char * file_output)
{
	// Lexer, grammar and generator
	lexer lex;
	grammar gra;
	generator gen;
	char * buffer;

	// Initialize the lexer, the grammar and the generator
	buffer = load_file(file_input);
	init_lexer(&lex, buffer);
	init_grammar(&gra, &lex);
	init_generator(&gen, &gra, file_output);
	// Do the magic stuff
	generate_code(&gen);
	// Release stuff adquired from the lexer, the grammar and the generator
	destroy_generator(&gen);
	destroy_grammar(&gra);
	destroy_lexer(&lex);
	free(buffer);
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
