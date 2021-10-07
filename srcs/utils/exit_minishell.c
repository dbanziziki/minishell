/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:19:57 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 13:19:58 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_minishell *ms, int status)
{
	int	i;

	free_all(ms);
	i = -1;
	while (ms->var->items[++i])
		free(ms->var->items[i]);
	free(ms->var->items);
	free(ms->var);
	free(ms);
	clear_history();
	exit(status);
}
