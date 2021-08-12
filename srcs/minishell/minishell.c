#include "minishell.h"
#include "libft.h"
#include <stdio.h>


void	minishell()
{
	t_minishell	*ms;
}

int	run_process(t_minishell *ms, t_cmd *cmd, t_AST *ast)
{
	int	i;

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
	return (0);
}

int main(int argc, char const *argv[])
{
	t_minishell	*ms;
	char		*line;
	t_cmd		*cmd;
	t_AST		*ast;
	int			nb_proc;
	pid_t		pid;
	t_program	*prog;
	char		curr_dir[1024];
	char		*dir;

	ms = init_minishell_struct();
	if (!ms)
		return (1);
	while (1)
	{
		getcwd(curr_dir, 1024);
		dir = ft_strjoin_sep(curr_dir, "> ", '-');
		#ifdef __APPLE__
		line = readline(dir);
		#else
		get_next_line(STDIN_FILENO, &line);
		#endif
		ms->ast = init_minishell_parse(&ms, line);
		prog = (t_program *)ms->ast->body;
		nb_proc = prog->nb_pipes + 1;
		ms->pipes = init_pipes(nb_proc + 1);
		ms->p_ids = (pid_t *)malloc(nb_proc * sizeof(pid_t));
		ms->nb_proc = nb_proc;
		ast = ms->ast->next; /* the first cmd to run */
		//run_process(ms, cmd, ast);// for (int i = 0; i < nb_proc; i++)
		for (int i = 0; i < nb_proc; i++)
		{
			ms->p_ids[i] = fork();
			if (ms->p_ids[i] == -1)
				return (1);
			if (ms->p_ids[i] == 0) /* child process */
			{
				/* closing all the unused pipes */
				close_unused_pipes(ms->pipes, nb_proc, i);
				cmd = (t_cmd *)ast->body;
				cmd->proc_idx = i;
				cmd_and_args(ms, ast, cmd);
				exit(EXIT_FAILURE);
				return (0); /* to avoid that the child process runs the for loop */
			}
			ast = ast->next; /* advence to the next cmd */
		}
		/* only the main process runs here */
		/* close all the pipes in the main process */
		close_main_pipes(ms->pipes, nb_proc);
		for (int i = 0; i < nb_proc; i++)
			waitpid(ms->p_ids[i], NULL, 0);
		/* free all the allocated memory */
		free(line);
		free(ms->p_ids);
		if (ms->pipes)
		{
			for (int i = 0; i < nb_proc + 1; i++)
				free(ms->pipes[i]);
		}
		free(ms->pipes);
		free(dir);
		free_all(ms->p, ms->ast);
	}
	return 0;
}
