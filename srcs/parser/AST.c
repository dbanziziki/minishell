/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:18:10 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:17:24 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*init_ast(int type, void *body)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->e_type = type;
	ast->body = body;
	ast->next = 0;
	return (ast);
}

void	addback_ast(t_ast **ast, t_ast *new)
{
	t_ast	*temp;

	if (!ast)
		return ;
	if (!(*ast))
	{
		*ast = new;
		return ;
	}
	temp = *ast;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}
