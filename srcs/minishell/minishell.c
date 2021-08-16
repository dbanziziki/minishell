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
	dir = ft_strjoin_sep(curr_dir, "> ", '-');
	line = readline(dir);
	free(dir);
	return (line);
}

int	post_child_process(t_minishell *ms, t_cmd *cmd, t_AST *ast)
{
	int	i;

	i = -1;
	close_main_pipes(ms->pipes, ms->nb_proc);
	while (++i < ms->nb_proc)
		waitpid(ms->p_ids[i], NULL, 0);
	/* free all the allocated memory */
	free(ms->p_ids);
	if (ms->pipes)
	{
		for (int i = 0; i < ms->nb_proc; i++)
			free(ms->pipes[i]);
	}
	free(ms->pipes);
	free_all(ms->p, ms->ast);
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
			cmd_and_args(ms, ast, cmd);
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
	temp->nb_proc = prog->nb_pipes + 1;
	temp->pipes = init_pipes(temp->nb_proc + 1);	
	temp->p_ids = (pid_t *)malloc(sizeof(pid_t) * temp->nb_proc);
	if (!temp->pipes || !temp->p_ids)
		return ;
}

void	minishell(char **env_v)
{
	t_minishell	*ms;
	char		*line;
	t_AST		*ast;

	ms = init_minishell_struct();
	if (!ms)
		return ;
	hook();
	while (1)
	{
		line = ms_readline();
		if (line == NULL)
			exit(0);
		if (!ft_strcmp(line, ""))
			continue ;		
		parse_line(&ms, line);

		ast = ms->ast->next; /* the first cmd to run */
		if (find_cmd(((t_cmd *)ast->body)->argv[0],
			((t_cmd *)ast->body)->argv[1], env_v))
		{
			ast = ast->next;
			free(line);
			continue ;
		}
		/// place for buildin commands !
		run_process(ms, ast);
		free(line);
	}
}

int main(int argc, char const *argv[], char **envp)
{
	minishell(envp);
	return 0;
}
