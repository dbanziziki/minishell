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
	int		i;
	char	*tmp;

	i = -1;
	ms->var = init_list(sizeof(char *));
	if (!ms->var)
		exit(1);
	while (env_v[++i])
	{
		tmp = ft_strdup(env_v[i]);
		if (!tmp)
			exit(1);
		list_push(ms->var, tmp);
	}
}

char	*get_env_v(char *key, t_array *var)
{
	int		i;
	char	*res;

	i = -1;
	while (++i < var->size)
	{
		if (!ft_strncmp(key, var->items[i], ft_strlen(key)))
		{
			res = ft_strchr(var->items[i], '=');
			if (!res)
			{
				// write(1, "\n", 1);
				return (NULL);
			}
			else
			{
				// printf("%s\n", &res[1]);
				return (&res[1]);
			}
		}	
	}
	// write(1, "\n", 1);
	return (NULL);
}

int	in_list(char *key, t_minishell *ms)
{
	int		i;
	char	*res;

	i = -1;
	while (++i < ms->var->size)
	{
		if (!ft_strncmp(key, ms->var->items[i], ft_strlen(key)))
			return (i);
	}
	return (-1);
}

void	export_v(t_minishell *ms, char *new_arg)
{
	char	*tmp;
	char	**tab;
	int		i;

	tab = ft_split(new_arg, '=');
	if (!tab || !tab[0])
		exit(1);
	i = in_list(tab[0], ms);
	if (i != -1)
	{
		if (tab[1])
		{
			tmp = ms->var->items[i];
			ms->var->items[i] = ft_strdup(new_arg);
			free(tmp);
		}
	}
	else
		list_push(ms->var, new_arg);
}

void    list_rm(t_array *list, void *to_rm, t_minishell *ms)
{
	char	**tmp;
	int		i;
	int		place;

	i = -1;
	if (!list->items)
		return ;
	tmp = malloc(((list->size + 1) * list->item_size));
	place = in_list(to_rm, ms);
	if (!tmp)
		exit(1);
	if (place == -1)
		return ;
	while (list->items[++i])
	{
		if (i < place)
			tmp[i] = list->items[i];
		else if (i == place)
			free(list->items[i]);
		else
			tmp[i - 1] = list->items[i];
	}
	free(list->items);
	list->items = (void **)tmp;
	list->size--;
	list->items[list->size] = 0;
}

void	unset(t_minishell *ms, char *var)
{
	if (!var || in_list(var, ms) == -1)
	{
		return ;
	}
	else
	{
		list_rm(ms->var, var, ms);
	}
}

int	find_cmd(t_array cmd, t_minishell *ms)
{
	if (cmd.items)
	{
		if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "echo"))
			echo((char **)cmd.items);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "cd"))
			change_dir((char *)cmd.items[1]);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "pwd"))
			pwd();
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "exit"))
			time_to_exit(ms);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "env"))
			get_env((char **)ms->var->items);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "env_v"))
			printf("%s\n", get_env_v((char *)cmd.items[1], ms->var));
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "export"))
			export_v(ms, (char *)cmd.items[1]);
		else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "unset"))
			unset(ms, (char *)cmd.items[1]);
		else
			return (0);
		return (1);
	}
	return (0);
}
