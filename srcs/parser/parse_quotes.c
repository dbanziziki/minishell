#include "parser.h"

static t_cmd	*create_cmd(t_parser *p, t_AST *last, t_token *token)
{
	char	*parsed;
	t_cmd	*cmd;

	cmd = NULL;
	parsed =  ft_strdup(token->value);
	if (last->e_type == PROGRAM)
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
	return (cmd);
}

static t_cmd	*set_cmd(t_parser *p, t_AST *last)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	token = eat(p, DOUBLE_QUOTE_TOKEN);
	if (!token)
		return (NULL);
	cmd = create_cmd(p, last, token);
	free(token->value);
	free(token);
	return (cmd);
}

void	parse_double_quotes(t_parser *p, t_AST *ast)
{
	t_cmd	*cmd;
	t_AST	*last;

	if (!p->token ||
		p->token->e_type != DOUBLE_QUOTE_TOKEN)
		return ;
	if (!p->token)
	{
		p->flag = 1;
		return ;
	}
	last = get_last(&ast);
	cmd = NULL;
	if (last->e_type != PROGRAM)
		cmd = (t_cmd *)last->body;
	cmd = set_cmd(p, last);
	if (!cmd)
		return ;
	eat_words(p, cmd);
	parse_double_quotes(p, ast);
}
