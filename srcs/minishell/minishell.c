#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	g_status;

static int	post_child_process(t_minishell *ms)
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

static int	run_process(t_minishell *ms, t_AST *ast)
{
	int		i;
	int		status;
	t_cmd	*cmd;

	i = -1;
	cmd = NULL;
	while (++i < ms->nb_proc)
	{
		ms->p_ids[i] = fork();
		if (ms->p_ids[i] == -1)
			return (1);
		if (ms->p_ids[i] == 0)
		{
			close_unused_pipes(ms->pipes, ms->nb_proc, i);
			cmd = (t_cmd *)ast->body;
			cmd->proc_idx = i;
			status = cmd_and_args(ms, ast);
			exit(status);
		}
		ast = ast->next;
	}
	post_child_process(ms);
	return (0);
}

static int	execute(t_minishell *ms, char *line)
{
	t_AST	*ast;

	parse_line(&ms, line);
	if (ms->p->flag == 1)
	{
		g_status = 258;
		free_all(ms);
		return (1);
	}
	ast = ms->ast->next;
	if (ast)
	{
		if (!ms->has_pipes && ast->body
			&& find_cmd(*((t_cmd *)ast->body)->argv, ms))
		{
			free_all(ms);
			free(line);
			return (1);
		}
		run_process(ms, ast);
	}
	return (0);
}

void	minishell(char **env_v)
{
	t_minishell	*ms;
	char		*line;
	t_AST		*ast;

	hook();
	ms = init_minishell_struct(env_v);
	while (1)
	{
		line = ms_readline();
		if (line == NULL)
			exit(EXIT_SUCCESS);
		if (!ft_strcmp(line, ""))
			continue ;
		if (execute(ms, line))
			continue ;
		free(line);
	}
}

void	minishell_arg(char **envp, char *line)
{
	t_minishell	*ms;
	t_AST		*ast;

	hook();
	ms = init_minishell_struct(envp);
	execute(ms, line);
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argv;
	(void)argc;
	if (!ft_strcmp(argv[1], "-c"))
		minishell_arg(envp, argv[2]);
	else
		minishell(envp);
	return (0);
}
