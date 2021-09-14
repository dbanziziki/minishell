#include "minishell.h"

/*
** Echo function reproduces behavior of "echo" bash command
**	but with limited functionality "-n" flag only.
*/
static void	echo_2(char **s, int i, char *flag)
{
	if (s[1] && !ft_strcmp("-n", s[1]))
	{
		flag = s[1];
		i = 1;
	}
	else
	{
		flag = NULL;
		i = 0;
	}
	while (s[++i])
	{
		write(1, s[i], ft_strlen(s[i]));
		if (s[i + 1])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}

void	for_dup(t_cmd *cmd)
{
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
	{
		dup2(cmd->save_out, STDOUT_FILENO);
		close(cmd->save_out);
	}
}

void	echo(char **s, t_AST *ast)
{
	char	*flag;
	int		i;
	t_cmd	*cmd;

	if (s)
	{
		cmd = (t_cmd *)ast->body;
		if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
				|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
			redirect_output(cmd);
		echo_2(s, i, flag);
	}
	for_dup(cmd);
}

/*
** The pwd function mimic behavior of "pwd" bash command.
*/

void	pwd(t_AST *ast)
{
	char	curr_dir[1024];
	t_cmd	*cmd;

	cmd = (t_cmd *)ast->body;
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
		redirect_output(cmd);
	getcwd(curr_dir, 1024);
	printf("%s\n", curr_dir);
	for_dup(cmd);
}

void	time_to_exit(t_minishell *ms, char **line)
{
	int	res;

	res = 0;
	if (line[1])
		res = ft_atoi(line[1]);
	exit_minishell(ms, res);
}
