#include "minishell.h"
#include "libft.h"

t_sig	g_sig;

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
	g_sig.exit_status = 0;
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

static void	check_env_var_exist(char **tab, t_minishell *ms, char *new_arg)
{
	char	*tmp;
	int		i;

	i = in_list(tab[0], ms);
	if (i != -1)
		put(ms, i, new_arg);
	else if (i == -1)
	{
		tmp = ft_strdup(new_arg);
		if (!tmp)
			exit_minishell(ms, EXIT_FAILURE);
		list_push(ms->var, tmp);
	}
}

void	export_v(t_minishell *ms, char **new_arg, t_AST *ast)
{
	char	**tab;
	char	*temp;

	if (!new_arg[0])
		return (sorted_exp(ms, ast));
	while (*++new_arg)
	{
		tab = ft_split(*new_arg, '=');
		temp = *new_arg;
		if (!tab)
			exit_minishell(ms, EXIT_FAILURE);
		if (!ft_strchr(temp, '='))
		{
			free_tab(tab);
			g_sig.exit_status = 0;
			return ;
		}
		check_env_var_exist(tab, ms, *new_arg);
		if (ft_isdigit(tab[0][0]))
		{
			g_sig.exit_status = 1;
			free_tab(tab);
			return (print_error("bash: export: not a valid identifier", NULL));
		}
		free_tab(tab);
		g_sig.exit_status = 0;
	}
}
