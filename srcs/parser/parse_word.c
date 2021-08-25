#include "parser.h"

t_cmd   *init_cmd(char *value)
{
    t_cmd   *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
        return (NULL);
    cmd->cmd = value;
    cmd->argv = init_list(sizeof(char *));
    cmd->io_mod = 0;
	cmd->proc_idx = 0;
	cmd->hd = 0;
    return (cmd);
}

t_io_mod    *init_io_mod(int type)
{
    t_io_mod    *io_mod;

    io_mod = (t_io_mod *)malloc(sizeof(t_io_mod));
	if (!io_mod)
		return (NULL);
    io_mod->type = type;
	io_mod->infile = NULL;
	io_mod->out = init_list(sizeof(char *));
    return (io_mod);
}

int	parse_word(t_parser *p, t_AST *ast)
{
	t_AST	*new;
	t_cmd	*cmd;
	t_token	*token;
	t_AST	*last;

	last = ast;
	while (last->next)
		last = last->next;
	token = eat(p, WORD_TOKEN);
	if (!token)
		return (1);
	if (last->type != PROGRAM)
	{
		cmd = (t_cmd *)last->body;
		if (!cmd->cmd)
			cmd->cmd = token->value;
	}
	else
		cmd = init_cmd(token->value);
    if (!cmd)
        return (-1);
	list_push(cmd->argv, token->value);
	free(token);
    /* geting the cmd arguments and pushing it in cmd->argv */
	eat_words(p, cmd);
	if (last->type == PROGRAM)
		addback_AST(&ast, init_AST(CMD_AND_ARG, cmd));
	return (1);
}
