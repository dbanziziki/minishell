#include "minishell.h"
#include "libft.h"
#include <stdio.h>

/*
** The change_dir function reproduces behavior of "cd" bash command
** but only with a relative or absolute path.
*/

void	move_to(t_minishell *ms, t_AST *ast, char *path)
{
	int		err;
	char	*goal;
	char	*new;
	char	curr_dir[1024];

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
		g_sig.exit_status = 1;
		return ;
	}
	export_v(ms, goal, ast);
	export_v(ms, new, ast);
	free(goal);
	free(new);
}

static int	err_check(char *goal, char *new, int err)
{
	if (!goal || !new)
	{
		printf("Malloc error\n");
		return (1);
	}
	if (err)
	{
		printf("cd: %s: No such file or directory \n", goal);
		g_sig.exit_status = 1;
		return (1);
	}
	return (0);
}

void	move_to_root(t_minishell *ms, t_AST *ast)
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
	export_v(ms, new, ast);
	export_v(ms, goal, ast);
	free(goal);
	free(new);
}

void	change_dir(char *path, t_minishell *ms, t_AST *ast)
{
	int		err;
	char	*goal;
	char	*new;

	if (path)
		move_to(ms, ast, path);
	else
		move_to_root(ms, ast);
}
