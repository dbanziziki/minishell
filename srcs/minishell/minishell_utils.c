#include "minishell.h"

t_minishell	*init_minishell_struct(void)
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

int	**init_pipes(int nb_pipes)
{
	int	**pipes;
	int	i;

	if (nb_pipes == 1)
		return (NULL);
	i = -1;
	pipes = (int **)malloc(sizeof(int *) * nb_pipes);
	if (!pipes)
		return (NULL);
	while (++i < nb_pipes)	
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) == -1)
		{
			while (--i)
			{
				close(pipes[i][0]);
				close(pipes[i][1]);
				free(pipes[i]);
			}
			return (NULL);
		}
	}
	return (pipes);
}

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

int	close_unused_pipes(int **pipes, int size, int i)
{
	int	j;

	j = -1;
	while (++j < size)
	{
		if (i != j)
		{
			if (close(pipes[j][0]) == -1)
				return (-1);
		}
		if (i + 1 != j)
		{
			if (close(pipes[j][1]) == -1)
				return (-1);
		}
	}
	return (0);
}