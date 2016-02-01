#include "token.h"

void init_token_int_type(token_int_type * token)
{
	token->base.type = INT_TYPE;
	token->base.token_pointer = token;
}

void init_token_int_value(token_int_value * token, int value)
{
	token->base.type = INT_VALUE;
	token->base.token_pointer = token;
	token->value = value;
}

void init_token_function(token_function * token, const char * value)
{
	token->base.type = FUNCTION;
	token->base.token_pointer = token;
	token->name = value;
}

void init_token_opar(token_opar * token)
{
	token->base.type = OPAR;
	token->base.token_pointer = token;
}

void init_token_cpar(token_cpar * token)
{
	token->base.type = CPAR;
	token->base.token_pointer = token;
}

void init_token_obra(token_obra * token)
{
	token->base.type = OBRA;
	token->base.token_pointer = token;
}

void init_token_cbra(token_cbra * token)
{
	token->base.type = CBRA;
	token->base.token_pointer = token;
}

void init_token_return(token_return * token)
{
	token->base.type = RETURN;
	token->base.token_pointer = token;
}

void init_token_semicolon(token_semicolon * token)
{
	token->base.type = SEMICOLON;
	token->base.token_pointer = token;
}

void init_token_eof(token_eof * token)
{
	token->base.type = END_OF_FILE;
	token->base.token_pointer = token;
}

