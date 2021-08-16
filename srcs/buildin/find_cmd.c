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

int	find_cmd(t_array cmd, t_array flags, char **env_v)
{
	// printf("--%s--\n", (char *)cmd.items[1]);
	// printf("--%s--\n", (char *)cmd.items[2]);
	if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "echo"))
		echo((char *)cmd.items[1], (char *)cmd.items[2]);
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "pwd"))
		pwd();
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "cd"))
		change_dir((char *)cmd.items[1]);
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "exit"))
		time_to_exit();
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "env"))
		get_env(env_v);
	else 
		return (0);
	return (1);
}
