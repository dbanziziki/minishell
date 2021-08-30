#include "parser.h"

static t_cmd	*set_cmd(t_parser *p, t_AST *last)
{
	t_token	*token;
	t_cmd	*cmd;
	char	*parsed;

	cmd = NULL;
	token = eat(p, DOUBLE_QUOTE_TOKEN);
	if (!token)
		return (NULL);
	parsed = parse_str(token->value, p->var);
	/* check if we have some env var to interpret in token->value */
	if (last->type == PROGRAM)
	{
		cmd = init_cmd(parsed);
		list_push(cmd->argv, parsed);
		addback_AST(&last, init_AST(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)last->body;
		list_push(cmd->argv, parsed);
	}
	free(token);
	token = NULL;
	return (cmd);
}

void	parse_double_quotes(t_parser *p, t_AST *ast)
{
	t_cmd	*cmd;
	t_AST	*last;
	char	*parsed;

	if (p->token->type != DOUBLE_QUOTE_TOKEN)
		return ;
	last = ast;
	while (last->next)
		last = last->next;
	cmd = NULL;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	cmd = set_cmd(p, last);
	if (!cmd)
		return ;
	eat_words(p, cmd);
	parse_double_quotes(p, ast);
}
