#include "minishell.h"

void	free_memory(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}

void	free_ptr_table(void **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free_memory(ptr[i]);
	free_memory(ptr);
}

void	free_cmd_and_arg(t_cmd *cmd)
{
	if (cmd->io_mod)
	{
		free_memory(cmd->io_mod->infile);
		if (cmd->io_mod->out->items)
			free_ptr_table(cmd->io_mod->out->items);
		free_memory(cmd->io_mod->out);
		free_memory(cmd->io_mod);
	}
	if (cmd->argv)
	{
		if (cmd->argv->items)
			free_ptr_table(cmd->argv->items);
		free(cmd->argv);
	}
	ft_lstclear(&(cmd->hd), free);
	free_memory(cmd);
}

void	free_ast(t_ast **ast)
{
	t_cmd	*cmd;
	t_ast	*temp;
	int		i;

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

void	free_all(t_minishell *ms)
{
	int	i;

	i = -1;
	if (ms->p->token)
		free_memory(ms->p->token->value);
	free_memory(ms->p->token);
	free_memory(ms->p->t);
	free_memory(ms->p);
	free_memory(ms->line);
	free_ast(&(ms->ast));
	free(ms->p_ids);
	if (ms->pipes)
	{
		while (++i < ms->nb_proc + 1)
			free(ms->pipes[i]);
		free(ms->pipes);
	}
}
