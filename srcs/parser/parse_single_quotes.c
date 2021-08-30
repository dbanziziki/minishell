#include "parser.h"

static t_cmd	*set_cmd(t_parser *p, t_AST *last)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, SIMPLE_QUOTE_TOKEN);
	if (!token)
		return (NULL);
	if (last->type == PROGRAM)
	{
		cmd = init_cmd(token->value);
		list_push(cmd->argv, token->value);
		addback_AST(&last, init_AST(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)last->body;
		list_push(cmd->argv, token->value);
	}
	free(token);
	return (cmd);
}

void	parse_single_quotes(t_parser *p, t_AST *ast)
{
	t_token *token;
	t_cmd	*cmd;
	t_AST	*last;

	if (p->token->type != SIMPLE_QUOTE_TOKEN)
		return ;
	last = ast;
	while (last->next)
		last = last->next;
	cmd = set_cmd(p, last);	
	eat_words(p, cmd);
	parse_single_quotes(p, ast);
}