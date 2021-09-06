#include "minishell.h"

/*
** Echo function reproduces behavior of "echo" bash command
**	but with limited functionality "-n" flag only.
*/

void	echo(char **s)
{
	char	*flag;
	int		i;

	if (s)
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

	if (path)
	{
		getcwd(curr_dir, 1024);
		goal = ft_strjoin("OLDPWD=", curr_dir);
		err = chdir(path);
		if (err || !goal)
			printf("CD function in trouble 2 \n");
		export_v(ms, goal);
	}
	else
	{
		getcwd(curr_dir, 1024);
		goal = get_env_v("HOME", ms->var);
		err = chdir(goal);
		goal = ft_strjoin("OLDPWD=", curr_dir);
		if (err || !goal)
			printf("CD function in trouble 2 \n");
		export_v(ms, goal);
		printf("%s\n", goal);
	}
	free(goal);
}

/*
** The pwd function reproduces behavior of "pwd" bash command.
*/

void	pwd(void)
{
	char	curr_dir[1024];

	getcwd(curr_dir, 1024);
	printf("%s\n", curr_dir);
}

void	time_to_exit(t_minishell *ms)
{
	exit_minishell(ms, EXIT_SUCCESS);
}
