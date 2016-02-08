#ifndef TOKEN_H
#define TOKEN_H

#include <stdlib.h>

enum token_type {
	T_INT_TYPE,
	T_INT_VALUE,
	T_FUNCTION,
	T_OPAR,
	T_CPAR,
	T_OBRA,
	T_CBRA,
	T_RETURN,
	T_SEMICOLON,
	T_END_OF_FILE
};

/*
 * Tokens for the parser
 */
typedef struct token_base
{
	enum token_type type;
	void * token_pointer;
} token_base;

typedef struct token_int_type
{
	token_base base;
} token_int_type;

typedef struct token_int_value
{
	token_base base;
	int value;
} token_int_value;

typedef struct token_function
{
	token_base base;
	const char * name;
} token_function;

typedef struct token_opar
{
	token_base base;
} token_opar;

typedef struct token_cpar
{
	token_base base;
} token_cpar;

typedef struct token_obra
{
	token_base base;
} token_obra;

typedef struct token_cbra
{
	token_base base;
} token_cbra;

typedef struct token_return
{
	token_base base;
} token_return;

typedef struct token_semicolon
{
	token_base base;
} token_semicolon;

typedef struct token_eof
{
	token_base base;
} token_eof;

/*
 * Init functions for the tokens
 */
void init_token_int_type(token_int_type * token);
void init_token_int_value(token_int_value * token, int  value);
void init_token_function(token_function * token, const char * name);
void init_token_opar(token_opar * token);
void init_token_cpar(token_cpar * token);
void init_token_obra(token_obra * token);
void init_token_cbra(token_cbra * token);
void init_token_return(token_return * token);
void init_token_semicolon(token_semicolon * token);
void init_token_eof(token_eof * token);

#endif //TOKEN_H
