#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	g_status;

char	*ms_readline()
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

int	post_child_process(t_minishell *ms, t_cmd *cmd, t_AST *ast)
{
	int	i;
	int	status;

	i = -1;
	close_main_pipes(ms->pipes, ms->nb_proc);
	while (++i < ms->nb_proc)
	{
		waitpid(ms->p_ids[i], &status, 0);
		g_status = WEXITSTATUS(status);
	}
	free_all(ms);
	return (0);
}

int	run_process(t_minishell *ms, t_AST *ast)
{
	int		i;
	int		status;
	t_cmd	*cmd;
	
	i = -1;
	while (++i < ms->nb_proc)
	{
		ms->p_ids[i] = fork();
		if (ms->p_ids[i] == -1)
			return (1);
		if (ms->p_ids[i] == 0) /* child process */
		{
			close_unused_pipes(ms->pipes, ms->nb_proc, i);
			cmd = (t_cmd *)ast->body;
			cmd->proc_idx = i;
			status = cmd_and_args(ms, ast);
			exit(status);
		}
		ast = ast->next; /* advence to the next cmd */
	}
	post_child_process(ms, cmd, ast);
	return (0);
}

void	parse_line(t_minishell **ms, char *line)
{
	t_minishell *temp;
	t_program	*prog;
	t_AST		*ast;

	temp = *ms;
	temp->ast = init_minishell_parse(ms, line);
	prog = (t_program *)temp->ast->body;
	(*ms)->has_pipes = prog->has_pipes;
	temp->nb_proc = prog->nb_pipes + 1;
	temp->nb_pipe = temp->nb_proc + 1;
	temp->pipes = init_pipes(temp->nb_pipe);
	temp->p_ids = (pid_t *)malloc(sizeof(pid_t) * temp->nb_proc);
	if (!temp->pipes || !temp->p_ids)
		return ;
}

void	minishell(char **env_v)
{
	t_minishell	*ms;
	char		*line;
	t_AST		*ast;
	t_cmd		*cmd;

	hook();
	ms = init_minishell_struct(env_v);
	while (1)
	{
		line = ms_readline();
		if (line == NULL)
			exit(0);
		if (!ft_strcmp(line, ""))
			continue ;
		parse_line(&ms, line);
		if (ms->p->flag == 1)
		{
			g_status = 258;
			free_all(ms);
			continue ;
		}
		ast = ms->ast->next; /* the first cmd to run */
		if (!ms->has_pipes && ast->body && find_cmd(*((t_cmd *)ast->body)->argv, ms))
		{
			free_all(ms);
			free(line);
			continue ;
		}
		free(line);
		run_process(ms, ast);
	}
}

int main(int argc, char const *argv[], char **envp)
{
	minishell(envp);
	return 0;
}
