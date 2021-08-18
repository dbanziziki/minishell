#include "minishell.h"

void    free_memory(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}

void    free_ptr_table(void **ptr)
{
	int i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

void    free_cmd_and_arg(t_cmd *cmd)
{
	if (cmd->io_mod)
	{
		free_memory(cmd->io_mod->outfile);
		free_memory(cmd->io_mod->infile);
		free_memory(cmd->io_mod);
	}
	if (cmd->argv)
	{
		if (cmd->argv->items)
			free_ptr_table(cmd->argv->items);
		free(cmd->argv);
	}
	free_memory(cmd);
}

void    free_ast(t_AST **ast)
{
	t_cmd       *cmd;
	t_AST       *temp;
	int         i;

	i = -1;
	free((*ast)->body);
	temp = (*ast)->next;
	free(*ast);
	*ast = temp;
	while (*ast)
	{
		cmd = (t_cmd *)((*ast)->body);
		if (cmd)
			free_cmd_and_arg(cmd);
		temp = (*ast)->next;
		free(*ast);
		*ast = temp;
	}
	*ast = NULL;
}

void    free_all(t_minishell *ms)
{
	int i;

	i = -1;
	free(ms->p->token->value);
	free(ms->p->token);
	free(ms->p);
	free_ast(&(ms->ast));
	free(ms->p_ids);
	if (ms->pipes)
	{
		while (++i < ms->nb_proc + 1)
			free(ms->pipes[i]);
		free(ms->pipes);
	}
	//free(ms);
}