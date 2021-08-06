#include "parser.h"
#include <stdio.h>

t_token	*eat(t_parser *p, t_type type)
{
	t_token	*token;

	token = p->lookahead;
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
	p->lookahead = get_next_token(p->t);
	return (token);
}

t_token	*word(t_parser *p)
{
	t_token	*new;

	new = eat(p, WORD);
	return (new);
}

t_AST	*program(t_parser **p)
{
	t_AST *AST;

	AST = malloc(sizeof(t_AST));
	if (!AST)
		return (NULL);
	AST->type = PROGRAM;
	AST->body = word(*p);
	AST->parser = *p;
	return (AST);
}

t_AST	*parse(char *str)
{
	t_tokenizer *t;
	t_parser	*p;

	t = init(str);
	p = (t_parser *)malloc(sizeof(t_parser));
	if (!p)
		return (NULL);
	p->t = t;
	p->lookahead = get_next_token(t);
	return (program(&p));
}

int main(int argc, char const *argv[])
{
	t_AST		*AST;
	t_parser	*p;

	AST = parse("echo grep");
	p = AST->parser;
	printf("%s\n", ((t_token *)AST->body)->value);
	printf("%s\n", p->lookahead->value);
	free(p->lookahead->value);
	free(p->lookahead);
	free(p->t);
	free(p);
	free(((t_token *)AST->body)->value);
	free(AST->body);
	free(AST);
	return 0;
}
