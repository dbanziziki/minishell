#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	in_list(char *key, t_minishell *ms)
{
	size_t	i;

	i = -1;
	while (++i < ms->var->size)
	{
		if (!ft_strncmp(key, ms->var->items[i], ft_strlen(key)))
			return (i);
	}
	return (-1);
}

void	list_rm(t_array *list, void *to_rm, t_minishell *ms)
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
		return ;
	else
		list_rm(ms->var, var, ms);
}
