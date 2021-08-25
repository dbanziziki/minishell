#include "minishell.h"
#include "libft.h"
#include <stdio.h>
// #include <readline/readline.h>

char	*ms_readline()
{
	char	*line;
	char	curr_dir[1024];
	char	*dir;

	getcwd(curr_dir, 1024);
	dir = ft_strjoin_sep(curr_dir, "\033[0;35m> ", '-');
	printf("\033[0m");
	#ifdef __APPLE__
	line = readline(dir);
	if (line && *line)
		add_history(line);
	#else
	get_next_line(STDIN_FILENO, &line);
	#endif
	free(dir);
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
		ms->exit_status = WEXITSTATUS(status);
	}
	printf("Exit status: %d\n", ms->exit_status);
	/* free all the allocated memory */
	free_all(ms);
	return (0);
}

int	run_process(t_minishell *ms, t_AST *ast)
{
	int		i;
	t_cmd	*cmd;
	
	i = -1;
	while (++i < ms->nb_proc)
	{
		ms->p_ids[i] = fork();
		if (ms->p_ids[i] == -1)
			return (1);
		if (ms->p_ids[i] == 0) /* child process */
		{
			/* closing all the unused pipes */
			close_unused_pipes(ms->pipes, ms->nb_proc, i);
			cmd = (t_cmd *)ast->body;
			cmd->proc_idx = i;
			cmd_and_args(ms, ast);
			exit(EXIT_FAILURE);
			return (0); /* to avoid that the child process runs the for loop */
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

	//hook();
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
			ms->exit_status = 1;
			free_all(ms);
			continue ;
		}
		ast = ms->ast->next; /* the first cmd to run */
		if (!ms->has_pipes && ast->body && find_cmd(*((t_cmd *)ast->body)->argv, ms))
		{
			ast = ast->next;
			free(line);
			continue ;
		}
		run_process(ms, ast);
		free(line);
	}
}

int main(int argc, char const *argv[], char **envp)
{
	minishell(envp);
	return 0;
}
