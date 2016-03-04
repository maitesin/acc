#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"

void init_lexer(lexer * l, const char * filename) {
	l->f = fopen(filename, "r");
	l->stack = NULL;
}

void destroy_lexer(lexer * l) {
	fclose(l->f);
}

void free_stack_base(stack_base * s)
{
	free(s);
}

struct token_base * next(lexer * l) {
	char buffer[512];
	char * buff_copy = NULL;
	int pos = 0;
	size_t state = 0;
	char tmp;
	void * result = NULL;
	stack_base * stack = NULL;

	if (l->stack != NULL)
	{
		stack_base * stack = l->stack;
		l->stack = l->stack->next;
		result = stack->token;
		stack->token = NULL;
		free_stack_base(stack);
		return result;
	}

	tmp = fgetc(l->f);
	while (!feof(l->f))
	{
		switch(state)
		{
		case 0:
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
			break;
		case 1:
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
		case 2:
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
		case 3:
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
			buff_copy = (char *) malloc(sizeof(char)*pos+1);
			strncpy(buff_copy, buffer, pos);
			buff_copy[pos] = '\0';
			result = (struct token_function *)
				malloc(sizeof(struct token_function));
			init_token_function(result, buff_copy);
			return result;
		case 4:
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

void push_back(lexer * l, token_base * t)
{
	stack_base * s = (stack_base *) malloc(sizeof(stack_base));
	s->token = t;
	s->next = l->stack;
	l->stack = s;
}
