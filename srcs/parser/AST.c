/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AST.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:18:10 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/06 15:19:15 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

t_AST	*init_AST(int type, void *body)
{
	t_AST	*AST;

	AST = malloc(sizeof(t_AST));
	if (!AST)
		return (NULL);
	AST->e_type = type;
	AST->body = body;
	AST->next = 0;
	return (AST);
}

void	addback_AST(t_AST **ast, t_AST *new)
{
	t_AST	*temp;

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
