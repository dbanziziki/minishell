#include "parser.h"

static t_cmd	*set_cmd(t_parser *p, t_AST *last)
{
	t_cmd	*cmd;
	t_token	*token;

	token = eat(p, WORD_TOKEN);
	if (!token)
		return (NULL);
	if (last->e_type != PROGRAM)
	{
		cmd = (t_cmd *)last->body;
		if (!cmd->cmd)
			cmd->cmd = token->value;
	}
	else
		cmd = init_cmd(token->value);
	list_push(cmd->argv, token->value);
	free(token);
	return (cmd);
}

int	parse_word(t_parser *p, t_AST *ast)
{
	t_cmd	*cmd;
	t_AST	*last;

	last = get_last(&ast);
	cmd = set_cmd(p, last);
	if (!cmd)
		return (-1);
	eat_words(p, cmd);
	if (last->e_type == PROGRAM)
		addback_AST(&ast, init_AST(CMD_AND_ARG, cmd));
	return (1);
}
