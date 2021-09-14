#include "minishell.h"
#include "libft.h"
#include <stdio.h>

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
	for_dup(cmd);
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

int	find_cmd(t_array cmd, t_minishell *ms, t_AST *ast)
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
			export_v(ms, (char *)cmd.items[1], ast);
		else if (!ft_strcmp((char *)cmd.items[0], "unset"))
			unset(ms, (char *)cmd.items[1]);
		else
			return (0);
		return (1);
	}
	return (0);
}
