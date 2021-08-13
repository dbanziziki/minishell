#include "minishell.h"

void	echo(char *s, char *flag)
{
	if (s)
	{
		if (!ft_strcmp(s, ""))
		{
			if (!flag)
				write(1, "\n", 1);
		}
		else
		{
			if (!flag)
			{
				write(1, s, ft_strlen(s));
				write(1, "\n", 1);
			}
			else if (!ft_strcmp(flag, "-n"))
				write(1, s, ft_strlen(s));
		}
	}

void	change_dir(char *path, char *current)
{
	opendir ///
}

void	cwd(void)
{
	getcwd ///
}

void	time_to_exit(void)
{
	exit(0); ///
}

