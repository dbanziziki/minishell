#include "minishell.h"

/*
** Echo function reproduces behavior of "echo" bash command
**	but with limited functionality "-n" flag only.
*/

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
		if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
				|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
		{
			dup2(cmd->save_out, STDOUT_FILENO);
			close(cmd->save_out);
		}
	}
}

/*
** The change_dir function reproduces behavior of "cd" bash command
** but only with a relative or absolute path.
*/

void	change_dir(char *path, t_minishell *ms)
{
	int		err;
	char	curr_dir[1024];
	char	*goal;
	char	*new;

	if (path)
	{
		getcwd(curr_dir, 1024);
		goal = ft_strjoin("OLDPWD=", curr_dir);
		err = chdir(path);
		getcwd(curr_dir, 1024);
		new = ft_strjoin("PWD=", curr_dir);
		if (!goal || !new)
		{
			printf("Malloc error\n");
			exit_minishell(ms, EXIT_FAILURE);
		}
		if (err)
		{
			printf("cd: %s: No such file or directory \n", path);
			return ;
		}
		export_v(ms, goal);
		export_v(ms, new);
	}
	else
	{
		getcwd(curr_dir, 1024);
		goal = get_env_v("HOME", ms->var);
		err = chdir(goal);
		goal = ft_strjoin("OLDPWD=", curr_dir);
		getcwd(curr_dir, 1024);
		new = ft_strjoin("PWD=", curr_dir);
		if (!goal || !new)
		{
			printf("Malloc error\n");
			exit_minishell(ms, EXIT_FAILURE);
		}
		if (err)
		{
			printf("cd: %s: No such file or directory \n", goal);
			return ;
		}
		export_v(ms, new);
		export_v(ms, goal);
	}
	free(goal);
	free(new);
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
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
	{
		dup2(cmd->save_out, STDOUT_FILENO);
		close(cmd->save_out);
	}
}

void	time_to_exit(t_minishell *ms)
{
	exit_minishell(ms, EXIT_SUCCESS);
}
