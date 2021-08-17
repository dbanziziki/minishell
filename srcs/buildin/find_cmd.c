#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	get_env(char **env_v)
{
	int	i;

	i = -1;
	while (env_v[++i])
		printf("%s\n", env_v[i]);
}

void	init_env(char **env_v, t_minishell *ms)
{
	int	i;
	int	len;

	i = -1;
	while (env_v[++i])
		;
	ms->env_v = malloc(sizeof(char *) * (i + 1));
	if (!ms->env_v)
		exit(1);
	ms->env_v[i] = NULL;
	i = -1;
	while (env_v[++i])
	{
		len = ft_strlen(env_v[i]);
		ms->env_v[i] = malloc(sizeof(char *) * len);
		if (!ms->env_v[i])
			exit(1);
		ft_strlcpy(ms->env_v[i], env_v[i], len + 1);
	}
}

char *get_env_v(char *key, t_minishell *ms)
{
	int		i;
	char	*res;

	i = -1;
	while (ms->env_v[++i])
	{
		// printf("%s\n", ms->env_v[i]);
		if (!ft_strncmp(key, ms->env_v[i], ft_strlen(key)))
		{
			res = ft_strdup(&ms->env_v[i][ft_strlen(key) + 1]);
			// return (&ms->env_v[i][ft_strlen(key) + 1]);
			return (res);
		}	
	}
	return (NULL);
}

int	find_cmd(t_array cmd, char **env_v, t_minishell *ms)
{
	// printf("--%s--\n", (char *)cmd.items[1]);
	// printf("--%s--\n", (char *)cmd.items[2]);
	if (cmd.items)
	{
		if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "echo"))
			echo((char **)cmd.items);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "cd"))
			change_dir((char *)cmd.items[1]);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "pwd"))
			pwd();
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "exit"))
			time_to_exit();
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "env"))
			get_env(env_v);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "env_v"))
			printf("%s\n", get_env_v((char *)cmd.items[1], ms));
		else
			return (0);
		return (1);
	}
	return (0);
}
