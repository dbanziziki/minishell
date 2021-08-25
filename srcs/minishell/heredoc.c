#include "minishell.h"

static int	write_line(int fd, t_heredoc *hd)
{
	char	*line;
	char	*parsed;

	line = readline("> ");
	while (line)
	{
		if (!ft_strcmp(hd->delimiter, line))
		{
			free(line);
			break;
		}
		parsed = parse_str(line);
		if (!parsed)
			return (-1);
		write(fd, parsed, ft_strlen(parsed));
		write(fd, "\n", 1);
		if (parsed)
			free(parsed);
		line = readline("> ");
	}
	return (0);
}

static int	exec_heredoc_cmd(int fd, t_heredoc *hd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
	execvp(hd->cmd->cmd, (char **)hd->cmd->argv->items);
	return (-1);
}

int	heredoc(t_minishell *ms, t_AST *curr_ast)
{
	char		*line;
	t_heredoc	*hd;
	int			fds[2];
	char		*parsed;

	hd = (t_heredoc *)curr_ast->body;
	if (pipe(fds) == -1)
		return (-1);
	if (write_line(fds[1], hd) == -1)
		return (-1);
	close(fds[1]);
	if (hd->cmd)
		exec_heredoc_cmd(fds[0], hd);
	return (1);
}