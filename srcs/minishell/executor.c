#include "minishell.h"

void	exec_cmd(t_AST *ast)
{
	t_cmd	*cmd;
	pid_t	id;
	int		status;

	cmd = (t_cmd *)ast->body;
	/*check if is pipe or not*/
	if (ast->next)
	{
		if (pipe(cmd->fds) == -1)
			return ;
	}
	id = fork();
	if (id == 0)
	{
		/*execute the cmd*/
	}
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
	{

	}
}

void	executor(t_AST *ast)
{
	t_AST	*first;

	first = ast->next; /* first cmd*/
	while (first)
	{
		exec_cmd(first);
		first = first->next;
	}
}