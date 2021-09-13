#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	g_status;

void	get_env(char **env_v, int flag, t_AST *ast)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	cmd = (t_cmd *)ast->body;
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
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
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
	{
		dup2(cmd->save_out, STDOUT_FILENO);
		close(cmd->save_out);
	}
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
			exit_minishell(ms, EXIT_FAILURE);
		list_push(ms->var, tmp);
	}
}

char	*get_env_v(char *key, t_array *var)
{
	size_t	i;
	char	*res;

	i = -1;
	while (++i < var->size)
	{
		if (!ft_strncmp(key, var->items[i], ft_strlen(key)))
		{
			res = ft_strchr(var->items[i], '=');
			if (!res)
				return (NULL);
			else
				return (&res[1]);
		}
	}
	return (NULL);
}

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

void	free_tab(char **tab)
{
	int len;

	len = -1;
	while(tab[++len])
		free(tab[len]);
	free(tab);
}

char **cp_tab(char **tab)
{
	char **new_tab;
	int len;

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

int	swap_lines(char **s1, char **s2)
{
	char	*temp;
	char	*to_free;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
	return (0);
}

void	sorted_exp(t_minishell *ms, t_AST *ast)
{
	char	**tab;
	int		j;
	int		i;
	char	*temp;
	char	*to_free;
	t_cmd	*cmd;

	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
		redirect_output(cmd);
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
	get_env(tab, 1);
	if (cmd->io_mod && (cmd->io_mod->type == REDIRECT_OUTPUT
			|| cmd->io_mod->type == REDIRECT_OUTPUT_APPEND))
	{
		dup2(cmd->save_out, STDOUT_FILENO);
		close(cmd->save_out);
	}
	free_tab(tab);
}

void	export_v(t_minishell *ms, char *new_arg, t_AST *ast)
{
	char	*tmp;
	char	**tab;
	int		i;

	if (!new_arg)
	{
		sorted_exp(ms, ast);
		return ;
	}
	tab = ft_split(new_arg, '=');
	if (!tab)
		exit_minishell(ms, EXIT_FAILURE);
	i = in_list(tab[0], ms);
	if (i != -1)
	{
		if (tab[1])
		{
			tmp = ms->var->items[i];
			ms->var->items[i] = ft_strdup(new_arg);
			if (!ms->var->items[i])
				exit_minishell(ms, EXIT_FAILURE);
			free(tmp);
		}
	}
	else
	{
		tmp = ft_strdup(new_arg);
		if (!tmp)
			exit_minishell(ms, EXIT_FAILURE);
		list_push(ms->var, tmp);
	}
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
		return ;
	else
		list_rm(ms->var, var, ms);
}

int	find_cmd(t_array cmd, t_minishell *ms, t_AST *ast)
{
	if (cmd.items && (char *)cmd.items[0])
	{
		if (!ft_strcmp((char *)cmd.items[0], "echo"))
			echo((char **)cmd.items, ast);
		else if (!ft_strcmp((char *)cmd.items[0], "cd"))
			change_dir((char *)cmd.items[1], ms);
		else if (!ft_strcmp((char *)cmd.items[0], "pwd"))
			pwd(ast);
		else if (!ft_strcmp((char *)cmd.items[0], "exit"))
			exit_minishell(ms, EXIT_SUCCESS);
		else if (!ft_strcmp((char *)cmd.items[0], "env"))
			get_env((char **)ms->var->items, 0, ast);
		else if (!ft_strcmp((char *)cmd.items[0], "export"))
			export_v(ms, (char *)cmd.items[1], ast);
		else if (!ft_strcmp((char *)cmd.items[0], "unset"))
			unset(ms, (char *)cmd.items[1]);
		else
			return (0);
		return (1);
	}
	return (0);
}
