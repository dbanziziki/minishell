#include "parser.h"
#include "AST.h"
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

t_AST	*parse_word(t_parser *p)
{
	t_AST	*new;
	t_cmd	*cmd;
	t_token	*token;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	token = eat(p, WORD_TOKEN);
	printf("TOKEN: [%s] VALUE: [%s]\n", token_to_str(token->type), token->value);
	cmd->cmd = token->value;
	cmd->argv = init_list(sizeof(char *));
	list_push(cmd->argv, token->value);
	free(token);
	while (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		list_push(cmd->argv, token->value);
		free(token);
		token = NULL;
	}
	return (init_AST(CMD_AND_ARG, cmd));
}
