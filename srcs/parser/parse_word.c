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
    return (cmd);
}

t_io_mod    *init_io_mod(char *infile, char *outfile, int type)
{
    t_io_mod    *io_mod;

    io_mod = (t_io_mod *)malloc(sizeof(t_io_mod));
	if (!io_mod)
		return (NULL);
    io_mod->infile = infile;
    io_mod->oufile = outfile;
    io_mod->type = type;
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
	//printf("TOKEN: [%s] VALUE: [%s]\n", token_to_str(token->type), token->value);
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
    /* when the output is redirected */
	if (p->token->type == GREATER_THAN_TOKEN)
	{
        /*TODO: chained redirection*/
		token = eat(p, GREATER_THAN_TOKEN);
		free(token->value);
		free(token);
		token = eat(p, WORD_TOKEN);
        cmd->io_mod = init_io_mod(NULL, token->value, REDIRECT_OUTPUT);
		free(token);
	}
	/* Input redirection */
	else if (p->token->type == LESS_THAN_TOKEN)
	{
		token = eat(p, LESS_THAN_TOKEN);
		free(token->value);
		free(token);
		if (cmd->argv->size > 2) /*if we already have argv we skip the token*/
		{
			token = eat(p, WORD_TOKEN);
			free(token->value);
			free(token);
		}
		else
		{
			token = eat(p, WORD_TOKEN);
			if (cmd->io_mod)
				cmd->io_mod->infile = token->value;
			else
				cmd->io_mod = init_io_mod(token->value, NULL, REDIRECT_INPUT);
			free(token);
		}
	}
	return (init_AST(CMD_AND_ARG, cmd));
}
