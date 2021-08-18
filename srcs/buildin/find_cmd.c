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

	i = -1;
	ms->var = init_list(sizeof(char *));
	if (!ms->var)
		exit(1);
	while (env_v[++i])
		list_push(ms->var, env_v[i]);
}

int get_env_v(char *key, t_minishell *ms)
{
	int		i;
	char	*res;

	i = -1;
	while (++i < ms->var->size)
	{
		if (!ft_strncmp(key, ms->var->items[i], ft_strlen(key)))
		{
			res = ft_strchr(ms->var->items[i], '=');
			if (!res)
			{
				write(1, "\n", 1);
				return (0);
			}
			else
			{
				printf("%s\n", res);
				return (1);
			}
			// res = ft_strdup(&ms->var->items[i][ft_strlen(key) + 1]);
		}	
	}
	write(1, "\n", 1);
	return (0);
}

// void	*ft_realloc(void *ptr, size_t size)
// {
// 	void	*new_ptr;

// 	new_ptr = malloc(;
// 	if (!new_ptr)
// 		exit(1);
	
// }

// int	get_list_size(char **tab)
// {
// 	int i;

// 	i 
// }

void	export_v(t_minishell *ms, char *new_arg)
{
	char	*new;
	int		len;

	// if (!ft_strchr(new_arg, '='))
	// {
	// 	len = ft_strlen(new_arg) + 1;
	// 	new = realloc(new_arg, len);
	// 	if (!new)
	// 		exit(1);
	// 	// ft_strlcat(new, "+", len);
	// 	new[len - 1] = '=';
	// 	printf("%s\n", new);
	// 	list_push(ms->var, new);
	// }
	// else 
		list_push(ms->var, new_arg);
	// get_env((char**)ms->var->items);
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
			get_env((char **)ms->var->items);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "env_v"))
			get_env_v((char *)cmd.items[1], ms);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "export"))
			export_v(ms, (char *)cmd.items[1]);
		else
			return (0);
		return (1);
	}
	return (0);
}
