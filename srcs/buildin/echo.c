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
		{
			write(1, "\n", 1);
		}
	}
}

/*
** The change_dir function reproduces behavior of "cd" bash command
** but only with a relative or absolute path.
*/

void	change_dir(char *path)
{
	int		err;
	char	curr_dir[1024];

	if (path)
	{
		err = chdir(path);
		if (err)
			printf("CD function in trouble 1 \n");
	}
	else
	{
		while (ft_strcmp("/", curr_dir))
		{
			err = chdir("..");
			if (err)
				printf("CD function in trouble 2 \n");
			getcwd(curr_dir, 1024);
		}
	}
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
	int	i;

	free_all(ms);
	i = -1;
	while (ms->var->items[++i])
		free(ms->var->items[i]);
	free(ms->var->items);
	free(ms->var);
	free(ms);
	exit(EXIT_SUCCESS);
}

