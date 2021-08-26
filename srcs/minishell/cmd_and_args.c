#include "minishell.h"
#include <stdio.h>

static int	redirect_output(t_cmd *cmd)
{
	t_io_mod	*io_mod;
	int			i;
	int			out_size;

	i = -1;
	io_mod = cmd->io_mod;
	out_size = io_mod->out->size;
	while (++i < io_mod->out->size - 1)
	{
		if (io_mod->type == REDIRECT_OUTPUT)
			io_mod->fds[1] = open(io_mod->out->items[i], O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else
			io_mod->fds[1] = open(io_mod->out->items[i], O_APPEND | O_CREAT | O_WRONLY, 0644);
		close(io_mod->fds[1]);
	}
	if (io_mod->type == REDIRECT_OUTPUT)
		io_mod->fds[1] = open(io_mod->out->items[out_size - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else
		io_mod->fds[1] = open(io_mod->out->items[out_size - 1], O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (cmd->io_mod->fds[1] < 0)
		return (1);
	dup2(io_mod->fds[1], STDOUT_FILENO);
	if (close(io_mod->fds[1]) == -1)
		return (1);
	return (0);
}

static int	redirect_input(t_cmd *cmd)
{
	cmd->io_mod->fds[0] = open(cmd->io_mod->infile, O_RDONLY);
	if (cmd->io_mod->fds[0] < 0)
	{
		printf("minishell: no file or directory: %s\n", cmd->io_mod->infile);
		exit(EXIT_FAILURE);
		return (1);
	}
	dup2(cmd->io_mod->fds[0], STDIN_FILENO);
	if (close(cmd->io_mod->fds[0]) == -1)
		return (1);
	return (0);
}

static void	pipe_stdout(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd)
{
	if (!(cmd->io_mod && cmd->io_mod->out->items))
		dup2(ms->pipes[cmd->proc_idx + 1][1], STDOUT_FILENO);
	/*close the used pipes*/
	if (curr_ast->next->type != PIPE_CMD_AND_ARG)
	{
		close(ms->pipes[cmd->proc_idx][0]);
		close(ms->pipes[cmd->proc_idx + 1][1]);
	}
}

static void	read_from_pipe(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd)
{
	if (cmd->io_mod && cmd->io_mod->infile)
		redirect_input(cmd);
	else
		dup2(ms->pipes[cmd->proc_idx][0], STDIN_FILENO);
	/*close the used pipes*/
	close(ms->pipes[cmd->proc_idx][0]);
	close(ms->pipes[cmd->proc_idx + 1][1]);
}

int cmd_and_args(t_minishell *ms, t_AST *curr_ast)
{
	t_cmd	*next_cmd;
	t_cmd	*cmd;

	next_cmd = NULL;
	cmd = (t_cmd *)curr_ast->body;
	if (cmd->hd)
		heredoc(ms, curr_ast);
	if (curr_ast->next)
		next_cmd = (t_cmd *)curr_ast->next->body;
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT ||
		cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
		redirect_output(cmd);
	else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT)
		redirect_input(cmd);
	else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT_OUTPUT)
	{
		redirect_input(cmd);
		redirect_output(cmd);
	}
	/* if the next next cmd needs input from the last command */
	if (next_cmd && cmd->proc_idx != ms->nb_proc - 1)
		pipe_stdout(ms, curr_ast, cmd);
	/*if true we need to read from a pipe*/
	if (curr_ast->type == PIPE_CMD_AND_ARG)
		read_from_pipe(ms, curr_ast, cmd);
	/* if no cmd dont create process*/
	if (!cmd->cmd)
		exit(EXIT_SUCCESS);
	if (find_cmd(*(cmd->argv), ms))
		return (1);
	else
		execvp(cmd->cmd, (char **)(cmd->argv->items));
	printf("minishell: command not found: %s\n", cmd->cmd);
	return (1);
}
