#include "minishell.h"

static void	free_split(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	test(int signum)
{
	printf("yep\n");
}

int	exec_cmd(t_cmd *cmd, t_array *var)
{
	char	**res;
	char	*path;
	char	*path_join;
	size_t	i;

	signal(SIGQUIT, &test);
	i = -1;
	if (!cmd)
		return (-1);
	path = get_env_v("PATH", var);
	if (!path)
		return (-1);
	res = ft_split(path, ':');
	if (!res)
		return (-1);
	while (res[++i])
	{
		execve(cmd->cmd, (char **)cmd->argv->items, (char **)var->items);
		path_join = ft_strjoin_sep(res[i], cmd->cmd, '/');
		if (!path_join)
			return (-1);
		execve(path_join, (char **)cmd->argv->items, (char **)var->items);
		free(path_join);
	}
	free_split(res);
	return (-1);
}
