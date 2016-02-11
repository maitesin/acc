#include "token.h"

/*
 * Init functions implementations
 */
void init_token_int_type(token_int_type * token)
{
	token->base.type = T_INT_TYPE;
	token->base.token_pointer = token;
}

void init_token_int_value(token_int_value * token, int value)
{
	token->base.type = T_INT_VALUE;
	token->base.token_pointer = token;
	token->value = value;
}

void init_token_function(token_function * token, char * value)
{
	token->base.type = T_FUNCTION;
	token->base.token_pointer = token;
	token->name = value;
}

void init_token_opar(token_opar * token)
{
	token->base.type = T_OPAR;
	token->base.token_pointer = token;
}

void init_token_cpar(token_cpar * token)
{
	token->base.type = T_CPAR;
	token->base.token_pointer = token;
}

void init_token_obra(token_obra * token)
{
	token->base.type = T_OBRA;
	token->base.token_pointer = token;
}

void init_token_cbra(token_cbra * token)
{
	token->base.type = T_CBRA;
	token->base.token_pointer = token;
}

void init_token_return(token_return * token)
{
	token->base.type = T_RETURN;
	token->base.token_pointer = token;
}

void init_token_semicolon(token_semicolon * token)
{
	token->base.type = T_SEMICOLON;
	token->base.token_pointer = token;
}

void init_token_eof(token_eof * token)
{
	token->base.type = T_END_OF_FILE;
	token->base.token_pointer = token;
}

/*
 * Release functions implementation
 */
void free_token_int_type(token_int_type * token)
{
	free(token);
}

void free_token_int_value(token_int_value * token)
{
	free(token);
}

void free_token_function(token_function * token)
{
	free(token);
}

void free_token_opar(token_opar * token)
{
	free(token);
}

void free_token_cpar(token_cpar * token)
{
	free(token);
}

void free_token_obra(token_obra * token)
{
	free(token);
}

void free_token_cbra(token_cbra * token)
{
	free(token);
}

void free_token_return(token_return * token)
{
	free(token);
}

void free_token_semicolon(token_semicolon * token)
{
	free(token);
}

void free_token_eof(token_eof * token)
{
	free(token);
}
