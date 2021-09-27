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

int	heredoc(t_minishell *ms, t_AST *curr_ast)
{
	t_cmd		*cmd;
	t_list		*hd;
	int			in;

	cmd = (t_cmd *)curr_ast->body;
	hd = cmd->hd;
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
	if (cmd->cmd)
		dup2(in, STDIN_FILENO);
	if (close(in) == -1)
		return (-1);
	return (1);
}
