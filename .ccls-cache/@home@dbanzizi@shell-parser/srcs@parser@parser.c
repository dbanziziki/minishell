#include <stdio.h>
#include "parser.h"

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
		printf("minishell: parse error near `%s`\n", token->value);
		exit(1);
		return (NULL);
	}
	p->token = get_next_token(p->t);
	return (token);
}

t_AST	*parse_pipe(t_parser *p)
{
	t_token	*token;

	token = eat(p, PIPE_TOKEN);
	return (init_AST(PROGRAM, NULL));
}

t_AST	*parse(t_parser *p, t_AST *ast)
{
	if (p->token->type == EOF_TOKEN)
		return (ast);
	if (p->token->type == WORD_TOKEN)
		addback_AST(&ast, parse_word(p));
	else
	{
		printf("unexpected token at `%s`\n", p->token->value);
		exit(1);
	}
	/*if (p->token->type == PIPE)
		addback_AST(&ast, parse_pipe(p));*/
	/*add a token to parse in an if statement*/
	parse(p, ast);
	return (ast);
}

