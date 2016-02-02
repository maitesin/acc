#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

void init_lexer(lexer * l, const char * filename) {
	l->f = fopen(filename, "r");
}

void destroy_lexer(lexer * l) {
	fclose(l->f);
}

struct token_base * next(lexer * l) {
	char buffer[512];
	int pos = 0;
	size_t state = 0;
	char tmp;
	void * result;

	tmp = fgetc(l->f);
	while (!feof(l->f))
	{
		if (state == 0) {
			if (tmp == '\t' || tmp == ' ' || tmp == '\n')
			{
				tmp = fgetc(l->f); // Skip these characters
			}
			else if (tmp == '0') {
				result = (struct token_int_value *)
					malloc(sizeof(struct token_int_value));
				init_token_int_value(result, 0);
				return result;
			} else if (tmp >= '1' && tmp <= '9')
			{
				buffer[pos++] = tmp;
				tmp = fgetc(l->f);
				state = 1;
			} else if (tmp == '(')
			{
				result = (struct token_opar *)
					malloc(sizeof(struct token_opar));
				init_token_opar(result);
				return result;
			} else if (tmp == ')')
			{
				result = (struct token_cpar *)
					malloc(sizeof(struct token_cpar));
				init_token_cpar(result);
				return result;
			} else if (tmp == '{')
			{
				result = (struct token_obra *)
					malloc(sizeof(struct token_obra));
				init_token_obra(result);
				return result;
			} else if (tmp == '}')
			{
				result = (struct token_cbra *)
					malloc(sizeof(struct token_cbra));
				init_token_cbra(result);
				return result;
			} else if (tmp == ';')
			{
				result = (struct token_semicolon *)
					malloc(sizeof(struct token_semicolon));
				init_token_semicolon(result);
				return result;
			} else if (tmp == 'i')
			{
				buffer[pos++] = tmp;
				tmp = fgetc(l->f);
				state = 2;
			} else if (tmp == 'm')
			{
				buffer[pos++] = tmp;
				tmp = fgetc(l->f);
				state = 3;
			} else if (tmp == 'r')
			{
				buffer[pos++] = tmp;
				tmp = fgetc(l->f);
				state = 4;
			}

		} else if (state == 1)
		{
			// Find the whole number
			while (tmp >= '0' && tmp <= '9') {
				buffer[pos++] = tmp;
				tmp = fgetc(l->f);
			}
			fseek(l->f, -1, SEEK_CUR);
			buffer[pos] = '\0';
			result = (struct token_int_value *)
				malloc(sizeof(struct token_int_value));
			init_token_int_value(result, atoi(buffer));
			return result;
		} else if (state == 2)
		{
			if (tmp != 'n')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 't')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			result = (struct token_int_type *)
				malloc(sizeof(struct token_int_type));
			init_token_int_type(result);
			return result;
		} else if (state == 3)
		{
			if (tmp != 'a')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 'i')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 'n')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			buffer[pos] = '\0';
			result = (struct token_function *)
				malloc(sizeof(struct token_function));
			init_token_function(result, buffer);
			return result;
		} else if (state == 4)
		{
			if (tmp != 'e')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 't')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 'u')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 'r')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			buffer[pos++] = tmp;
			tmp = fgetc(l->f);
			if (tmp != 'n')
			{
				// Could be a function or a variable name
				exit(EXIT_FAILURE);
			}
			result = (struct token_return *)
				malloc(sizeof(struct token_return));
			init_token_return(result);
			return result;
		}
	}
	result = (struct token_eof *) malloc(sizeof(struct token_eof));
	init_token_eof(result);
	return result;
}
