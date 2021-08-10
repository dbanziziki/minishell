#include "minishell.h"

int	redirect_output(t_cmd *cmd)
{
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

int cmd_and_args(t_AST *head, t_cmd *cmd)
{
	if (head->body)
	{
		printf("nb pipes [%d]\n", ((t_program *)head->body)->nb_pipes);
	}
	if (cmd->io_mod && cmd->io_mod->type == REDIRECT_OUTPUT)
		redirect_output(cmd);	
	else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT)
		redirect_input(cmd);
	execvp(cmd->cmd, (char **)(cmd->argv->items));
	printf("minishell: command not found: %s\n", cmd->cmd);
	return (1);
}
