#include "minishell.h"
#include "libft.h"
#include <stdio.h>

void	free_tab(char **tab)
{
	int	len;

	len = -1;
	while (tab[++len])
		free(tab[len]);
	free(tab);
}

char	**cp_tab(char **tab)
{
	char	**new_tab;
	int		len;

	len = -1;
	while (tab[++len])
		;
	new_tab = malloc(sizeof(char *) * (len + 1));
	if (!new_tab)
		return (NULL);
	new_tab[len] = NULL;
	len = -1;
	while (tab[++len])
	{
		new_tab[len] = ft_strdup(tab[len]);
		if (!new_tab[len])
			return (NULL);
	}
	return (new_tab);
}

void	sorted_exp(t_minishell *ms, t_AST *ast)
{
	char	**tab;
	int		j;
	int		i;
	char	*temp;
	char	*to_free;

	tab = cp_tab((char **)ms->var->items);
	if (!tab)
		exit_minishell(ms, EXIT_FAILURE);
	i = -1;
	j = -1;
	while (tab[++i])
	{
		while (tab[++j])
		{
			if (ft_strcmp(tab[i], tab[j]) < 0)
			{
				if (swap_lines(&tab[i], &tab[j]))
					exit_minishell(ms, EXIT_FAILURE);
			}
		}
		j = -1;
	}
	get_env(tab, 1, ast);
	free_tab(tab);
}

static void	put(t_minishell *ms, int i, char *new_arg)
{
	char	*tmp;

	tmp = ms->var->items[i];
	ms->var->items[i] = ft_strdup(new_arg);
	if (!ms->var->items[i])
		exit_minishell(ms, EXIT_FAILURE);
	free(tmp);
}

void	export_v(t_minishell *ms, char *new_arg, t_AST *ast)
{
	char	*tmp;
	char	**tab;
	int		i;

	if (!new_arg)
		return (sorted_exp(ms, ast));
	tab = ft_split(new_arg, '=');
	if (!tab)
		exit_minishell(ms, EXIT_FAILURE);
	i = in_list(tab[0], ms);
	if (i != -1 && tab[1])
		put(ms, i, new_arg);
	else if (i == -1)
	{
		tmp = ft_strdup(new_arg);
		if (!tmp)
			exit_minishell(ms, EXIT_FAILURE);
		list_push(ms->var, tmp);
	}
	free_tab(tab);
}
