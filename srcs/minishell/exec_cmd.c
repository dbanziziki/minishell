#include "minishell.h"

static void	free_split(char **split)
{
	size_t	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static void	find_and_exec(t_cmd *cmd, t_array *var, char *res)
{
	char	*path_join;

	execve(cmd->cmd, (char **)cmd->argv->items, (char **)var->items);
	path_join = ft_strjoin_sep(res, cmd->cmd, '/');
	if (!path_join)
		return ;
	execve(path_join, (char **)cmd->argv->items, (char **)var->items);
	free(path_join);
}

int	exec_cmd(t_cmd *cmd, t_array *var)
{
	char	**res;
	char	*path;
	size_t	i;

	i = -1;
	if (!cmd)
		return (-1);
	path = get_env_v("PATH", var);
	if (!path)
		return (-1);
	res = ft_split(path, ':');
	if (!res)
		return (-1);
	hook();
	while (res[++i])
		find_and_exec(cmd, var, res[i]);
	free_split(res);
	return (-1);
}
