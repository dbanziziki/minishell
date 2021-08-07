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
	t_AST		*ast;
	t_program	*prog;
	t_cmd		*cmd;
	t_token		*token;

	prog = (t_program *)malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	ast = init_AST(PROGRAM, prog);
	token = eat(p, WORD);
	prog->has_pipes = 0;
	prog->nb_pipes = 0;
	if (token->type == WORD)
		addback_AST(&ast, word(token, p));
	return (ast);
}

t_AST	*word(t_token *curr_token, t_parser *p)
{
	t_AST	*new;
	t_cmd	*cmd;
	t_token	*token;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = curr_token->value;
	free(curr_token);
	token = eat(p, WORD);
	cmd->argv = init_list(sizeof(char *));
	while (token->type == WORD)
	{
		list_push(cmd->argv, token->value);
		free(token);
		token = eat(p, p->token->type);
	}
	//NOT THE GOOD PLACE TO FREE
	free(token->value);
	free(token);
	return (init_AST(CMD_AND_ARG, cmd));
}
