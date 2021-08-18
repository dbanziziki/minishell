#include "parser.h"

t_cmd   *init_cmd(char *value)
{
    t_cmd   *cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
        return (NULL);
    cmd->cmd = value;
    cmd->argv = init_list(sizeof(char *));
    cmd->io_mod = NULL;
	cmd->proc_idx = 0;
    return (cmd);
}

t_io_mod    *init_io_mod(int type)
{
    t_io_mod    *io_mod;

    io_mod = (t_io_mod *)malloc(sizeof(t_io_mod));
	if (!io_mod)
		return (NULL);
    io_mod->type = type;
	io_mod->in = init_list(sizeof(char *));
	io_mod->out = init_list(sizeof(char *));
    return (io_mod);
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
    cmd = init_cmd(token->value);
    if (!cmd)
        return (NULL);
	list_push(cmd->argv, token->value);
	free(token);
    /* geting the cmd arguments and pushing it in cmd->argv */
	while (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		list_push(cmd->argv, token->value);
		free(token);
		token = NULL;
	}
	return (init_AST(CMD_AND_ARG, cmd));
}
