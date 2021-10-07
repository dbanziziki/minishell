/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:58:33 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:58:34 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_unused_pipes(int **pipes, int size, int i)
{
	int	j;

	j = -1;
	while (++j < size)
	{
		if (i != j)
		{
			if (close(pipes[j][0]) == -1)
				return (-1);
		}
		if (i + 1 != j)
		{
			if (close(pipes[j][1]) == -1)
				return (-1);
		}
	}
	return (1);
}

int	close_main_pipes(int **pipes, int size)
{
	int	i;

	i = -1;
	while (++i < size + 1)
	{
		if (i != size)
			close(pipes[i][0]);
		if (i != 0)
			close(pipes[i][1]);
	}
	close(pipes[0][1]);
	close(pipes[size][0]);
	return (1);
}

t_minishell	*init_minishell_struct(char **env_v)
{
	t_minishell	*ms;

	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		return (NULL);
	init_env(env_v, ms);
	ms->ast = 0;
	ms->p = 0;
	ms->pipes = 0;
	ms->p_ids = 0;
	return (ms);
}

t_ast	*init_minishell_parse(t_minishell **ms, char *str)
{
	t_ast		*ast;
	t_program	*prog;
	t_parser	*p;

	p = init_parser(str);
	prog = init_prog();
	if (!prog || !p)
		return (NULL);
	ast = init_ast(PROGRAM, prog);
	p->t->envp = (*ms)->var;
	p->var = (*ms)->var;
	parse(p, &ast);
	if (!ast)
		return (NULL);
	(*ms)->ast = ast;
	(*ms)->p = p;
	return (ast);
}

int	**init_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	if (nb_pipes == 1)
		return (NULL);
	i = -1;
	pipes = (int **)malloc(sizeof(int *) * nb_pipes);
	if (!pipes)
		return (NULL);
	while (++i < nb_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			return (NULL);
		}
	}
	return (pipes);
}
