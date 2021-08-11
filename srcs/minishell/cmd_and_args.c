#include "minishell.h"
#include <stdio.h>

int	close_main_pipes(int **pipes, int size, int i)
{
	int	j;

	j = -1;
	while (++j < size)
	{
		if (j != i)
		{
			if (close(pipes[j][0]) == -1)
				return (-1);
		}
		if (j != 0)
		{
			if (close(pipes[j][1]) == -1)
				return (-1);
		}
	}
	return (0);
}

int	close_used_pipes(int **pipes, int i)
{
	if (close(pipes[i + 1][1]) == -1)
		return (-1);
	if (close(pipes[i][0]) == -1)
		return (-1);
	return (0);
}

int	redirect_output(t_cmd *cmd)
{
	/*TODO: handle append */
	cmd->io_mod->fds[1] = open(cmd->io_mod->oufile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (cmd->io_mod->fds[1] < 0)
		return (1);
	dup2(cmd->io_mod->fds[1], STDOUT_FILENO);
	if (close(cmd->io_mod->fds[1]) == -1)
		return (1);
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	cmd->io_mod->fds[0] = open(cmd->io_mod->infile, O_RDONLY);
	if (cmd->io_mod->fds[0] < 0)
		return (1);
	dup2(cmd->io_mod->fds[0], STDIN_FILENO);
	if (close(cmd->io_mod->fds[0]) == -1)
		return (1);
	return (0);
}

int cmd_and_args(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd)
{
	t_cmd	*next_cmd;
	t_AST	*head;

	/*might have priority*/
	head = ms->ast;
	next_cmd = NULL;
	if (curr_ast->next)
		next_cmd = (t_cmd *)curr_ast->next->body;
	if (cmd->io_mod && cmd->io_mod->type == REDIRECT_OUTPUT)
		redirect_output(cmd);
	else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT)
		redirect_input(cmd);
	/* if it's the first process and we have a pipe */
	if (next_cmd && cmd->proc_idx != ms->nb_proc - 1)
	{
		//printf("process index is %d About to redirect to %s\n", cmd->proc_idx ,next_cmd->cmd);
		//if it's the first process, write in pipe for the next command
		dup2(ms->pipes[cmd->proc_idx + 1][1], STDOUT_FILENO);
		// close the used pipes
		if (curr_ast->next->type != PIPE_CMD_AND_ARG)
		{
			close(ms->pipes[cmd->proc_idx][0]);
			close(ms->pipes[cmd->proc_idx + 1][1]);
		}
	}
	if (curr_ast->type == PIPE_CMD_AND_ARG) // if the type is good we need to read from a pipe
	{
		//read input from the last command
		//printf("About to read last command process index is %d\n", cmd->proc_idx);
		dup2(ms->pipes[cmd->proc_idx][0], STDIN_FILENO);
		//close the used pipes
		close(ms->pipes[cmd->proc_idx][0]);
		close(ms->pipes[cmd->proc_idx + 1][1]);
	}
	/* not clear yet up to here */
	//printf("About to execute %s\n", cmd->cmd);
	execvp(cmd->cmd, (char **)(cmd->argv->items));
	printf("minishell: command not found: %s\n", cmd->cmd);
	return (1);
}
