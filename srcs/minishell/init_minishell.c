#include "minishell.h"

char	*ms_readline(void)
{
	char	*line;
	char	curr_dir[1024];
	char	*dir;
	char	*temp;

	getcwd(curr_dir, 1024);
	dir = ft_strjoin("\033[0;32m", curr_dir);
	temp = dir;
	dir = ft_strjoin_sep(dir, ">\033[0m ", '-');
	line = readline(dir);
	if (line)
		add_history(line);
	free(dir);
	free(temp);
	return (line);
}

void	parse_line(t_minishell **ms, char *line)
{
	t_minishell	*temp;
	t_program	*prog;

	temp = *ms;
	temp->ast = init_minishell_parse(ms, line);
	prog = (t_program *)temp->ast->body;
	(*ms)->has_pipes = prog->has_pipes;
	temp->nb_proc = prog->nb_pipes + 1;
	temp->nb_pipe = temp->nb_proc + 1;
	temp->pipes = init_pipes(temp->nb_pipe);
	temp->p_ids = (pid_t *)malloc(sizeof(pid_t) * temp->nb_proc);// TODO
	if (!temp->pipes || !temp->p_ids)
		return ;
}
