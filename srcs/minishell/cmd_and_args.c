/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_and_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:57:58 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:57:59 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	redirections(t_cmd *cmd)
{
	if (cmd->io_mod && (cmd->io_mod->e_type == REDIRECT_OUTPUT
			|| cmd->io_mod->e_type == REDIRECT_OUTPUT_APPEND))
	{
		if (redirect_output(cmd) < 0)
			return (-1);
	}
	else if (cmd->io_mod && cmd->io_mod->e_type == REDIRECT_INPUT)
	{
		if (redirect_input(cmd))
			return (-1);
	}
	else if (cmd->io_mod && (cmd->io_mod->e_type == REDIRECT_INPUT_OUTPUT
			|| cmd->io_mod->e_type == REDIRECT_INPUT_OUTPUT_APPEND))
	{
		if (redirect_input(cmd) < 0)
			return (-1);
		if (redirect_output(cmd) < 0)
			return (-1);
	}
	return (0);
}

static int	pipes(t_minishell *ms, t_ast *curr_ast, t_cmd *cmd)
{
	t_cmd	*next_cmd;

	next_cmd = NULL;
	if (curr_ast->next)
		next_cmd = (t_cmd *)curr_ast->next->body;
	if (next_cmd && cmd->proc_idx != ms->nb_proc - 1)
	{
		if (pipe_stdout(ms, curr_ast, cmd) < 0)
			return (-1);
	}
	if (curr_ast->e_type == PIPE_CMD_AND_ARG && !cmd->hd)
	{
		if (read_from_pipe(ms, cmd) < 0)
			return (-1);
	}
	return (0);
}

int	cmd_and_args(t_minishell *ms, t_ast *curr_ast)
{
	t_cmd	*next_cmd;
	t_cmd	*cmd;

	next_cmd = NULL;
	cmd = (t_cmd *)curr_ast->body;
	if (cmd->hd)
		heredoc(ms, curr_ast);
	if (curr_ast->next)
		next_cmd = (t_cmd *)curr_ast->next->body;
	if (redirections(cmd) < 0)
		return (1);
	if (pipes(ms, curr_ast, cmd) < 0)
		return (-1);
	if (!cmd->cmd)
		exit(EXIT_SUCCESS);
	if (find_cmd(*(cmd->argv), ms, curr_ast))
		return (0);
	else
		exec_cmd(cmd, ms->var);
	print_error("minishell: command not found: ", cmd->cmd);
	return (127);
}
