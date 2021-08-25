#include "parser.h"

static t_io_mod	*create_io_mod(t_token *token, int type)
{
	t_io_mod	*io_mod;

	io_mod = NULL;
	if (type == LESS_THAN_TOKEN)
	{
		io_mod = init_io_mod(REDIRECT_INPUT);
		io_mod->infile = token->value;
	}
	else if (type == GREATER_THAN_TOKEN)
	{
		io_mod = init_io_mod(REDIRECT_OUTPUT);
		list_push(io_mod->out, token->value);
	}
	else
	{
		io_mod = init_io_mod(REDIRECT_OUTPUT_APPEND);
		list_push(io_mod->out, token->value);			
	}
	return (io_mod);
}

static t_io_mod	*set_io_mod(t_cmd *cmd, t_token *token, int type)
{
	t_io_mod	*io_mod;

	if (cmd && cmd->io_mod)
	{
		if (type == LESS_THAN_TOKEN)
		{
			if (cmd->io_mod->infile)
				free(cmd->io_mod->infile);
			cmd->io_mod->infile = token->value;
		}
		else
			list_push(cmd->io_mod->out, token->value);
		if (cmd->io_mod->out->size > 0 && cmd->io_mod->infile)
			cmd->io_mod->type = REDIRECT_INPUT_OUTPUT;
		return (cmd->io_mod);
	}
	else
		io_mod = create_io_mod(token, type);
	return (io_mod);
}

static t_io_mod	*parse_redirect(t_parser *p, t_cmd *cmd, int type)
{
	t_token		*token;
	t_io_mod	*io_mod;

	token = eat(p, type);
	free(token->value);
	free(token);
	token = eat(p, WORD_TOKEN);
	io_mod = set_io_mod(cmd, token, type);
	if (!io_mod)
		return (NULL);
	free(token);
	return (io_mod);
}

static void	parse_cmd_and_args(t_parser *p, t_AST **ast, t_io_mod *io_mod)
{
	t_cmd	*cmd;
	t_token	*token;

	token = NULL;
	cmd = NULL;
	if (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		cmd = init_cmd(token->value);
		list_push(cmd->argv, token->value);
		free(token);
		eat_words(p, cmd);
		cmd->io_mod = io_mod;
	}
	else
	{
		cmd = init_cmd(NULL);
		cmd->io_mod = io_mod;
	}
	addback_AST(ast, init_AST(CMD_AND_ARG, cmd));
}

void parse_redirections(t_parser *p, t_AST *ast)
{
	t_cmd		*cmd;
	t_AST		*last;
	t_io_mod	*io_mod;

	last = ast;
	cmd = NULL;
	while (last->next)
		last = last->next;
	if (last->type == CMD_AND_ARG)
		cmd = (t_cmd *)last->body;
	if (p->token->type == GREATER_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, GREATER_THAN_TOKEN);
	else if (p->token->type == LESS_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, LESS_THAN_TOKEN);
	else if (p->token->type == GGREATER_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, GGREATER_THAN_TOKEN);
	if (cmd == NULL)
		parse_cmd_and_args(p, &ast, io_mod);
	else
	{
		cmd->io_mod = io_mod;
	}
}