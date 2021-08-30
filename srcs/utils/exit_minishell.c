#include "minishell.h"

void    exit_minishell(t_minishell *ms)
{
    int i;

    free_all(ms);
    i = -1;
	while (ms->var->items[++i])
		free(ms->var->items[i]);
	free(ms->var->items);
	free(ms->var);
	free(ms);
	exit(EXIT_SUCCESS);
}