/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <kkalinic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:28:06 by kkalinic          #+#    #+#             */
/*   Updated: 2021/10/07 14:29:03 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>

static void	cond(t_minishell *ms, char *line)
{
	int		num;
	char	*tmp;
	char	*tmp_2;

	if (!ft_strncmp(line, "SHLVL=", 6))
	{
		num = ft_atoi(&line[6]);
		tmp = ft_itoa(++num);
		tmp_2 = ft_strjoin("SHLVL=", tmp);
		if (!tmp || !tmp_2)
			exit_minishell(ms, EXIT_FAILURE);
		free(tmp);
		tmp = tmp_2;
	}
	else
		tmp = ft_strdup(line);
	if (!tmp)
		exit_minishell(ms, EXIT_FAILURE);
	list_push(ms->var, tmp);
}

void	init_env(char **env_v, t_minishell *ms)
{
	int		i;

	i = -1;
	ms->var = init_list(sizeof(char *));
	if (!ms->var)
		exit(1);
	while (env_v[++i])
	{
		cond(ms, env_v[i]);
	}
}

int	swap_lines(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
	return (0);
}

char	*get_env_v(char *key, t_array *var)
{
	size_t	i;
	char	*res;

	i = -1;
	if (!key)
		return (NULL);
	while (++i < var->size)
	{
		res = ft_strchr(var->items[i], '=');
		if (res && !ft_strncmp(key, var->items[i],
				ft_strlen(var->items[i]) - ft_strlen(res)))
		{
			if (!res)
				return (NULL);
			else
				return (&res[1]);
		}
	}
	return (NULL);
}

int	find_cmd(t_array cmd, t_minishell *ms, t_ast *ast)
{
	if (cmd.items && (char *)cmd.items[0])
	{
		if (!ft_strcmp((char *)cmd.items[0], "echo"))
			echo((char **)cmd.items, ast);
		else if (!ft_strcmp((char *)cmd.items[0], "cd"))
			change_dir((char *)cmd.items[1], ms, ast);
		else if (!ft_strcmp((char *)cmd.items[0], "pwd"))
			pwd(ast);
		else if (!ft_strcmp((char *)cmd.items[0], "exit"))
			time_to_exit(ms, &cmd);
		else if (!ft_strcmp((char *)cmd.items[0], "env"))
			get_env((char **)ms->var->items, 0, ast);
		else if (!ft_strcmp((char *)cmd.items[0], "export"))
			export_v(ms, (char **)(cmd.items), ast);
		else if (!ft_strcmp((char *)cmd.items[0], "unset"))
			unset(ms, (char **)(cmd.items));
		else
			return (0);
		return (1);
	}
	return (0);
}
