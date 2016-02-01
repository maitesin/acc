#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

typedef struct lexer
{
	FILE * f;
} lexer;

void init_lexer(lexer * l, const char * filename);
void destroy_lexer(lexer * l);
struct token_base * next(lexer * l);

#endif //LEXER_H
