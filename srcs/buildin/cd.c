#include "minishell.h"
#include "libft.h"
#include <stdio.h>

/*
** The change_dir function reproduces behavior of "cd" bash command
** but only with a relative or absolute path.
*/
static int	check(char *path, char *goal, char *new, int err)
{
	if (!goal)
	{
		printf("Malloc error\n");
		return (2);
	}
	if (!new)
	{
		free(goal);
		printf("Malloc error\n");
		return (2);
	}
	if (err)
	{
		printf("cd: %s: No such file or directory \n", path);
		free(goal);
		free(new);
		g_sig.exit_status = 1;
		return (1);
	}
	return (0);
}

void	move_to(t_minishell *ms, t_ast *ast, char *path)
{
	int		err;
	char	*goal;
	char	*new;
	int		fl;
	char	curr_dir[1024];

	getcwd(curr_dir, 1024);
	goal = ft_strjoin("OLDPWD=", curr_dir);
	err = chdir(path);
	getcwd(curr_dir, 1024);
	new = ft_strjoin("PWD=", curr_dir);
	fl = check(path, goal, new, err);
	if (fl == 1)
		return ;
	else if (fl == 2)
		exit_minishell(ms, EXIT_FAILURE);
	export_v(ms, &goal, ast);
	export_v(ms, &new, ast);
	free(goal);
	free(new);
	g_sig.exit_status = 0;
}

static int	err_check(char *goal, char *new, int err)
{
	if (!goal)
	{
		printf("Malloc error\n");
		return (1);
	}
	if (!new)
	{
		free(goal);
		printf("Malloc error\n");
		return (1);
	}
	if (err)
	{
		printf("cd: %s: No such file or directory \n", goal);
		g_sig.exit_status = 1;
		return (0);
	}
	return (0);
}

void	move_to_root(t_minishell *ms, t_ast *ast)
{
	int		err;
	char	*goal;
	char	*new;
	char	curr_dir[1024];

	getcwd(curr_dir, 1024);
	goal = get_env_v("HOME", ms->var);
	err = chdir(goal);
	goal = ft_strjoin("OLDPWD=", curr_dir);
	getcwd(curr_dir, 1024);
	new = ft_strjoin("PWD=", curr_dir);
	if (err_check(goal, new, err))
		exit_minishell(ms, EXIT_FAILURE);
	export_v(ms, &new, ast);
	export_v(ms, &goal, ast);
	free(goal);
	free(new);
	g_sig.exit_status = 0;
}

void	change_dir(char *path, t_minishell *ms, t_ast *ast)
{
	if (path)
		move_to(ms, ast, path);
	else
		move_to_root(ms, ast);
}
