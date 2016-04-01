#include "token.h"

/*
 * Init functions implementations
 */
void init_token_int_type(token_int_type * token)
{
	token->base.type = T_INT_TYPE;
}

void init_token_int_value(token_int_value * token, int value)
{
	token->base.type = T_INT_VALUE;
	token->value = value;
}

void init_token_function(token_function * token, char * value)
{
	token->base.type = T_FUNCTION;
	token->name = value;
}

void init_token_opar(token_opar * token)
{
	token->base.type = T_OPAR;
}

void init_token_cpar(token_cpar * token)
{
	token->base.type = T_CPAR;
}

void init_token_obra(token_obra * token)
{
	token->base.type = T_OBRA;
}

void init_token_cbra(token_cbra * token)
{
	token->base.type = T_CBRA;
}

void init_token_return(token_return * token)
{
	token->base.type = T_RETURN;
}

void init_token_semicolon(token_semicolon * token)
{
	token->base.type = T_SEMICOLON;
}

void init_token_eof(token_eof * token)
{
	token->base.type = T_END_OF_FILE;
}

void init_token_if(token_if * token)
{
	token->base.type = T_IF;
}

void init_token_else(token_else * token)
{
	token->base.type = T_ELSE;
}

void init_token_boolean_op(token_boolean_op * token, char * op)
{
	token->base.type = T_BOOLEAN_OP;
	token->op = op;
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
	if (token->name != NULL)
		free(token->name);
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

void free_token_if(token_if * token)
{
	free(token);
}

void free_token_else(token_else * token)
{
	free(token);
}

void free_token_boolean_op(token_boolean_op * token)
{
	if (token->op != NULL)
		free(token->op);
	free(token);
}
