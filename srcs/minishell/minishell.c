#include "minishell.h"
#include <stdio.h>

void free_all(t_parser *p, t_AST *root)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)root->next->body;
	if (cmd->io_mod)
	{
		if (cmd->io_mod->infile)
			free(cmd->io_mod->infile);
		if (cmd->io_mod->oufile)
			free(cmd->io_mod->oufile);
		free(cmd->io_mod);
	}
	while (++i < cmd->argv->size)
		free(cmd->argv->items[i]);
	free(cmd->argv->items);
	free(cmd->argv);
	free(cmd);
	free(root->next);
	free(p->token->value);
	free(p->token);
	free(p->t);
	free(p);
	free(root->body);
	free(root);
}

t_program	*init_prog()
{
	t_program	*prog;

	prog = (t_program *)malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	prog->nb_pipes = 0;
	prog->nb_pipes = 0;
	return (prog);
}

t_minishell	*init_minishell_struct()
{
	t_minishell	*ms;

	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		return (NULL);
	ms->ast = 0;
	ms->p = 0;
	ms->pipes = 0;
	ms->p_ids = 0;
	return (ms);
}

t_AST	*init_minishell_parse(t_minishell **ms, char *str)
{
	t_AST		*ast;
	t_program	*prog;
	t_parser	*p;

	p = init_parser(str);
	prog = init_prog();
	if (!prog || !p)
		return (NULL);
	ast = init_AST(PROGRAM, prog);
	ast = parse(p, ast);
	if (!ast)
		return (NULL);
	(*ms)->ast = ast;
	(*ms)->p = p;
	return (ast);
}

int	**init_pipes(int nb_proc)
{
	int	**pipes;
	int	i;

	if (nb_proc == 1)
		return (NULL);
	i = -1;
	pipes = (int **)malloc(sizeof(int *));
	if (!pipes)
		return (NULL);
	while (++i < nb_proc)	
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i)
				free(pipes[i]);
			return (NULL);
		}
	}
	return (pipes);
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
		dir = ft_strjoin_sep(curr_dir, "> ", ' ');
		line = readline(dir);
		ms->ast = init_minishell_parse(&ms, line);
		prog = (t_program *)ms->ast->body;
		nb_proc = prog->nb_pipes + 1;
		ms->pipes = init_pipes(nb_proc);
		ms->p_ids = (pid_t *)malloc(nb_proc * sizeof(pid_t));
		ast = ms->ast->next; /* the first cmd to run */
		for (int i = 0; i < nb_proc; i++)
		{
			ms->p_ids[i] = fork();
			if (ms->p_ids[i] == -1)
				return (1);
			/* close all the unused pipes */
			if (ms->p_ids[i] == 0)
			{
				cmd = (t_cmd *)ast->body;
				cmd->proc_idx = i;
				cmd_and_args(ms->ast, cmd);
				return (0); /* to avoid that the child process runs the for loop */
			}
			ast = ast->next; /* advence to the next cmd */
		}
		for (int i = 0; i < nb_proc; i++)
			waitpid(ms->p_ids[i], NULL, 0);
		free(line);
		free(ms->p_ids);
		if (ms->pipes)
		{
			for (int i = 0; i < nb_proc; i++)
				free(ms->pipes[i]);
		}
		free(ms->pipes);
		free(dir);
		free_all(ms->p, ms->ast);
	}
	return 0;
}
