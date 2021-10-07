/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkalinic <kkalinic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:28:22 by kkalinic          #+#    #+#             */
/*   Updated: 2021/10/07 14:28:23 by kkalinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig;
/*
** Echo function reproduces behavior of "echo" bash command
**	but with limited functionality "-n" flag only.
*/

static void	echo_2(char **s)
{
	int		i;
	char	*flag;

	if (s[1] && !ft_strcmp("-n", s[1]))
	{
		flag = s[1];
		i = 1;
	}
	else
	{
		flag = NULL;
		i = 0;
	}
	while (s[++i])
	{
		write(1, s[i], ft_strlen(s[i]));
		if (s[i + 1])
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}

void	for_dup(t_cmd *cmd)
{
	if (cmd->io_mod && (cmd->io_mod->e_type == REDIRECT_OUTPUT
			|| cmd->io_mod->e_type == REDIRECT_OUTPUT_APPEND))
	{
		dup2(cmd->save_out, STDOUT_FILENO);
		close(cmd->save_out);
	}
}

void	echo(char **s, t_ast *ast)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ast->body;
	if (s)
	{
		if (cmd->io_mod && (cmd->io_mod->e_type == REDIRECT_OUTPUT
				|| cmd->io_mod->e_type == REDIRECT_OUTPUT_APPEND))
			redirect_output(cmd);
		echo_2(s);
	}
	g_sig.exit_status = 0;
	for_dup(cmd);
}

/*
** The pwd function mimic behavior of "pwd" bash command.
*/

void	pwd(t_ast *ast)
{
	char	curr_dir[1024];
	t_cmd	*cmd;

	cmd = (t_cmd *)ast->body;
	if (cmd->io_mod && (cmd->io_mod->e_type == REDIRECT_OUTPUT
			|| cmd->io_mod->e_type == REDIRECT_OUTPUT_APPEND))
		redirect_output(cmd);
	getcwd(curr_dir, 1024);
	printf("%s\n", curr_dir);
	for_dup(cmd);
}

void	time_to_exit(t_minishell *ms, t_array *cmd)
{
	int		res;
	size_t	i;
	char	*line;

	res = 0;
	i = -1;
	line = (char *)cmd->items[1];
	if (line)
	{
		while (line[++i] && (ft_isdigit(line[i]) || ft_isspace(line[i])))
			;
		res = ft_atoi(line);
		if (i != ft_strlen(line))
		{
			print_error("minishell: exit: numeric argument required", NULL);
			res = 255;
		}
		if (cmd->size > 2)
		{
			print_error("minishell: exit: too many arguments", NULL);
			g_sig.exit_status = 1;
			return ;
		}
	}
	exit_minishell(ms, res);
}
