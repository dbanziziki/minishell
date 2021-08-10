#include "minishell.h"
#include <stdio.h>

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

int	close_used_pipes(int **pipes, int i)
{
	if (close(pipes[i + 1][1]) == -1)
		return (-1);
	if (close(pipes[i][0]) == -1)
		return (-1);
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
	/* if it's not the first process */
	if (next_cmd && cmd->proc_idx != 0) 
	{
		close_used_pipes(ms->pipes, cmd->proc_idx);
		dup2(ms->pipes[cmd->proc_idx][0], STDIN_FILENO);
	}
	/* not clear yet up to here */
	execvp(cmd->cmd, (char **)(cmd->argv->items));
	printf("minishell: command not found: %s\n", cmd->cmd);
	return (1);
}
