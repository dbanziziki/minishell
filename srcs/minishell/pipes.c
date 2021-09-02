#include "minishell.h"

int	pipe_stdout(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd)
{
	if (!(cmd->io_mod && cmd->io_mod->out->items))
		dup2(ms->pipes[cmd->proc_idx + 1][1], STDOUT_FILENO);
	if (curr_ast->next->type != PIPE_CMD_AND_ARG)
	{
		if (close(ms->pipes[cmd->proc_idx][0]) < 0 ||
			close(ms->pipes[cmd->proc_idx + 1][1]) < 0)
			return (-1);
	}
	return (0);
}

int	read_from_pipe(t_minishell *ms, t_cmd *cmd)
{
	if (cmd->io_mod && cmd->io_mod->infile)
	{
		if (redirect_input(cmd) < 0)
			return (-1);
	}
	else
		dup2(ms->pipes[cmd->proc_idx][0], STDIN_FILENO);
	if (close(ms->pipes[cmd->proc_idx][0]) < 0 ||
		close(ms->pipes[cmd->proc_idx + 1][1]) < 0)
		return (-1);
	return (0);
}
