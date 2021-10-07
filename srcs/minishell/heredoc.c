/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 11:58:10 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 12:10:46 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_line(t_list *hd, t_array *var)
{
	int		fds[2];
	char	*line;
	char	*parsed;

	line = readline("> ");
	if (pipe(fds) == -1)
		return (-1);
	while (line)
	{
		if (!ft_strcmp(hd->content, line))
		{
			free(line);
			break ;
		}
		parsed = parse_str(line, var);
		if (!parsed)
			return (-1);
		write(fds[1], parsed, ft_strlen(parsed));
		write(fds[1], "\n", 1);
		if (parsed)
			free(parsed);
		line = readline("> ");
	}
	close(fds[1]);
	return (fds[0]);
}

static int	exec_herodoc(t_minishell *ms, t_list *hd)
{
	int	in;

	while (hd)
	{
		if (!ft_strcmp(hd->content, "NULL"))
		{
			print_error("minishell: parse error near ", "`newline'");
			return (-1);
		}
		in = write_line(hd, ms->var);
		if (in < 0)
			return (-1);
		if (hd->next)
		{
			if (close(in) < 0)
				return (-1);
		}
		hd = hd->next;
	}
	return (in);
}

int	heredoc(t_minishell *ms, t_ast *curr_ast)
{
	t_cmd		*cmd;
	t_list		*hd;
	int			in;

	cmd = (t_cmd *)curr_ast->body;
	hd = cmd->hd;
	in = exec_herodoc(ms, hd);
	if (in < 0)
		return (-1);
	if (cmd->cmd)
		dup2(in, STDIN_FILENO);
	if (close(in) == -1)
		return (-1);
	return (1);
}
