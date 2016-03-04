#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

typedef struct stack_base
{
	struct stack_base * next;
	token_base * token;
} stack_base;

typedef struct lexer
{
	FILE * f;
	stack_base * stack;
} lexer;

void init_lexer(lexer * l, const char * filename);
void destroy_lexer(lexer * l);
void free_stack_base(stack_base * b);
struct token_base * next(lexer * l);
void push_back(lexer * l, token_base * t);

#endif //LEXER_H
