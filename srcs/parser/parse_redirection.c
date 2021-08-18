#include "parser.h"

static t_io_mod	*set_io_mod(t_cmd *cmd, t_token *token, int type)
{
	t_io_mod	*io_mod;

	if (cmd && cmd->io_mod)
	{
		if (cmd->io_mod->type == REDIRECT_INPUT)
			cmd->io_mod->outfile = token->value;
		else
			cmd->io_mod->infile = token->value;
		cmd->io_mod->type = REDIRECT_INPUT_OUTPUT;
		return (cmd->io_mod);
	}
	else
	{
		if (type == LESS_THAN_TOKEN)
			io_mod = init_io_mod(token->value, NULL, REDIRECT_INPUT);
		else if (type == GREATER_THAN_TOKEN)
			io_mod = init_io_mod(NULL, token->value, REDIRECT_OUTPUT);
		else
			io_mod = init_io_mod(NULL, token->value, REDIRECT_OUTPUT_APPEND);
	}
	return (io_mod);
}

static t_io_mod	*parse_redirect(t_parser *p, t_cmd *cmd, int type)
{
	t_token		*token;
	t_io_mod	*io_mod;

	/*TODO: chained redirection*/
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
		while (p->token->type == WORD_TOKEN)
		{
			token = eat(p, WORD_TOKEN);
			list_push(cmd->argv, token->value);
			free(token);
			token = NULL;
		}
		cmd->io_mod = io_mod;
	}
	else
	{
		cmd = init_cmd(NULL);
		cmd->io_mod = io_mod;
	}
	addback_AST(ast, init_AST(CMD_AND_ARG, cmd));
}

void parse_redirection(t_parser *p, t_AST *ast)
{
	t_cmd		*cmd;
	t_AST		*last;
	t_io_mod	*io_mod;
	t_token		*token;

	last = ast;
	cmd = NULL;
	while (last->next)
		last = last->next;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	if (p->token->type == GREATER_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, GREATER_THAN_TOKEN);
	else if (p->token->type == LESS_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, LESS_THAN_TOKEN);
	else if (p->token->type == GGREATER_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, GGREATER_THAN_TOKEN);
	if (last->type == PROGRAM)
		parse_cmd_and_args(p, &ast, io_mod);
	else
		cmd->io_mod = io_mod;
	if (last->next && last->next->body)
		cmd = (t_cmd *)last->next->body;
}