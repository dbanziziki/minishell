/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:22 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:14:58 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_io_mod	*create_io_mod(t_token *token, int type)
{
	t_io_mod	*io_mod;

	io_mod = NULL;
	if (type == LESS_THAN_TOKEN)
	{
		io_mod = init_io_mod(REDIRECT_INPUT);
		io_mod->hd_flag = 0;
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
			cmd->io_mod->hd_flag = 0;
			if (cmd->io_mod->infile)
				free(cmd->io_mod->infile);
			cmd->io_mod->infile = token->value;
		}
		else
			list_push(cmd->io_mod->out, token->value);
		if (cmd->io_mod->out->size > 0 && cmd->io_mod->infile
			&& type == GREATER_THAN_TOKEN)
			cmd->io_mod->e_type = REDIRECT_INPUT_OUTPUT;
		else if (cmd->io_mod->out->size > 0 && cmd->io_mod->infile
			&& type == GGREATER_THAN_TOKEN)
			cmd->io_mod->e_type = REDIRECT_INPUT_OUTPUT_APPEND;
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
	if (p->flag)
		return (NULL);
	token = eat(p, WORD_TOKEN);
	if (!token)
		return (NULL);
	io_mod = set_io_mod(cmd, token, type);
	if (!io_mod)
		return (NULL);
	free(token);
	return (io_mod);
}

static void	parse_cmd_and_args(t_parser *p, t_ast **ast, t_io_mod *io_mod)
{
	t_cmd	*cmd;
	t_token	*token;

	token = NULL;
	cmd = NULL;
	if (p->token->e_type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		if (!token)
			return ;
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
	addback_ast(ast, init_ast(CMD_AND_ARG, cmd));
}

void	parse_redirections(t_parser *p, t_ast *ast)
{
	t_cmd		*cmd;
	t_ast		*last;
	t_io_mod	*io_mod;

	last = get_last(&ast);
	cmd = NULL;
	io_mod = NULL;
	if (last->e_type != PROGRAM)
		cmd = (t_cmd *)last->body;
	if (p->token->e_type == GREATER_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, GREATER_THAN_TOKEN);
	else if (p->token->e_type == LESS_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, LESS_THAN_TOKEN);
	else if (p->token->e_type == GGREATER_THAN_TOKEN)
		io_mod = parse_redirect(p, cmd, GGREATER_THAN_TOKEN);
	if (!io_mod)
		return ;
	if (cmd == NULL)
		parse_cmd_and_args(p, &ast, io_mod);
	else
		cmd->io_mod = io_mod;
}
