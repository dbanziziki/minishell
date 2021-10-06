#include "minishell.h"

t_sig	g_sig;

static int	post_child_process(t_minishell *ms)
{
	int	i;
	int	status;

	i = -1;
	close_main_pipes(ms->pipes, ms->nb_proc);
	while (++i < ms->nb_proc)
	{
		waitpid(ms->p_ids[i], &status, 0);
		if (g_sig.exit_status == SIGQUIT)
			g_sig.exit_status = 128 + SIGQUIT;
		else if (g_sig.exit_status == SIGINT)
			g_sig.exit_status = 128 + SIGINT;
		else
		{
			if (ms->p->hd_err)
				g_sig.exit_status = 258;
			else
				g_sig.exit_status = WEXITSTATUS(status);
		}
	}
	free_all(ms);
	return (0);
}

static int	run_process(t_minishell *ms, t_AST *ast)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	cmd = NULL;
	while (++i < ms->nb_proc)
	{
		ms->p_ids[i] = fork();
		g_sig.id = ms->p_ids[i];
		if (ms->p_ids[i] == -1)
			return (1);
		if (ms->p_ids[i] == 0)
		{
			close_unused_pipes(ms->pipes, ms->nb_proc, i);
			cmd = (t_cmd *)ast->body;
			cmd->proc_idx = i;
			g_sig.exit_status = cmd_and_args(ms, ast);
			exit(g_sig.exit_status);
		}
		ast = ast->next;
	}
	post_child_process(ms);
	return (g_sig.exit_status);
}

int	execute(t_minishell *ms, char *line)
{
	t_AST	*ast;

	parse_line(&ms, line);
	if (ms->p->flag == 1)
	{
		g_sig.exit_status = 258;
		return (1);
	}
	ast = ms->ast->next;
	if (ast)
	{
		if (!ms->has_pipes && ast->body
			&& find_cmd(*((t_cmd *)ast->body)->argv, ms, ast))
		{
			free_all(ms);
			if (!g_sig.exit_status)
				g_sig.exit_status = 0;
			return (g_sig.exit_status);
		}
		g_sig.exit_status = run_process(ms, ast);
	}
	return (g_sig.exit_status);
}

void	minishell(char **env_v)
{
	t_minishell	*ms;

	ms = init_minishell_struct(env_v);
	while (1)
	{
		g_sig.id = 0;
		g_sig.sig_int = 0;
		g_sig.sig_quit = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &action);
		ms->line = ms_readline();
		if (ms->line == NULL)
			ms->line = ft_strdup("exit");
		if (!ft_strcmp(ms->line, ""))
		{
			free(ms->line);
			continue ;
		}
		if (execute(ms, ms->line))
			continue ;
	}
}

int	main(int argc, char *argv[], char **envp)
{
	if (argc >= 2 && !ft_strcmp(argv[1], "-c"))
		return (minishell_arg(envp, argv[2]));
	else
		minishell(envp);
	return (0);
}
