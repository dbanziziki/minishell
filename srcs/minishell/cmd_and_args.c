#include "minishell.h"

static	int	redirections(t_cmd *cmd)
{
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT ||
		cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
	{
		if (redirect_output(cmd) < 0)
			return (-1);
	}
	else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT)
	{
		if (redirect_input(cmd))
			return (-1);
	}
	else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT_OUTPUT)
	{
		if (redirect_input(cmd) < 0)
			return (-1);
		if (redirect_output(cmd) < 0)
			return (-1);
	}
	return (0);
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
	if (redirections(cmd) < 0)
		return (1);
	/* if the next next cmd needs input from the last command */
	if (next_cmd && cmd->proc_idx != ms->nb_proc - 1)
		pipe_stdout(ms, curr_ast, cmd);
	/*if true we need to read from a pipe*/
	if (curr_ast->type == PIPE_CMD_AND_ARG && !cmd->hd)
		read_from_pipe(ms, curr_ast, cmd);
	/* if no cmd dont create process*/
	if (!cmd->cmd)
		exit(EXIT_SUCCESS);
	if (find_cmd(*(cmd->argv), ms))
		return (1);
	else
		execvp(cmd->cmd, (char **)(cmd->argv->items));
	printf("minishell: command not found: %s\n", cmd->cmd);
	return (127);
}
