#include "parser.h"
#include <stdio.h>

t_parser	*init_parser(char *str)
{
	t_tokenizer	*t;
	t_parser	*p;

	t = init_tokenizer(str);
	if (!t)
		return (NULL);
	p = (t_parser *)malloc(sizeof(t_parser));
	if (!t)
		return (NULL);
	p->t = t;
	p->token = get_next_token(t);
	return (p);
}

t_token	*eat(t_parser *p, int type)
{
	t_token	*token;

	token = p->token;
	if (!token)
	{
		printf("unexpected end of input\n");
		return (NULL);
	}
	if (token->type != type)
	{
		printf("wrong token type\n");
		return (NULL);
	}
	p->token = get_next_token(p->t);
	return (token);
}

t_AST	*parse(t_parser *p)
{
	t_AST	*AST;

	AST = init_AST(PROGRAM);
	return (AST);
}

t_AST	*word(t_parser *p)
{
	t_AST	*new;

	while (p->token->type != EOF_TOKEN)
	{
		new = parse(p);
	}
	return (init_AST(PROGRAM));
}

