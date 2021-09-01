#include "minishell.h"

void	pipe_stdout(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd)
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

void	read_from_pipe(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd)
{
	if (cmd->io_mod && cmd->io_mod->infile)
		redirect_input(cmd);
	else
		dup2(ms->pipes[cmd->proc_idx][0], STDIN_FILENO);
	/*close the used pipes*/
	close(ms->pipes[cmd->proc_idx][0]);
	close(ms->pipes[cmd->proc_idx + 1][1]);
}
