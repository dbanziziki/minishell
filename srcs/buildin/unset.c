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

void	get_env(char **env_v, int flag, t_AST *ast)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	cmd = (t_cmd *)ast->body;
	if (cmd->io_mod && (cmd->io_mod->e_type == REDIRECT_OUTPUT
			|| cmd->io_mod->e_type == REDIRECT_OUTPUT_APPEND))
		redirect_output(cmd);
	if (!flag)
	{
		while (env_v[++i])
			printf("%s\n", env_v[i]);
	}
	else
	{
		while (env_v[++i])
			printf("declare -x %s\n", env_v[i]);
	}
	g_sig.exit_status = 0;
	for_dup(cmd);
}

void	list_mv(t_array *list, char **tmp, int place)
{
	int		i;

	i = -1;
	while (list->items[++i])
	{
		if (i < place)
			tmp[i] = list->items[i];
		else if (i == place)
			free(list->items[i]);
		else
			tmp[i - 1] = list->items[i];
	}
}

void	list_rm(t_array *list, void *to_rm, t_minishell *ms)
{
	char	**tmp;
	int		place;

	if (!list->items)
		return ;
	tmp = malloc(((list->size + 1) * list->item_size));
	place = in_list(to_rm, ms);
	if (!tmp)
		exit(1);
	if (place == -1)
		return ;
	list_mv(list, tmp, place);
	free(list->items);
	list->items = (void **)tmp;
	list->size--;
	list->items[list->size] = 0;
}

void	unset(t_minishell *ms, char **var)
{
	while (*++var)
	{
		// printf("%d \n", in_list(*var, ms));
		if (in_list(*var, ms) == -1)
			continue ;
		else
			list_rm(ms->var, *var, ms);
		g_sig.exit_status = 0;
	}
}
