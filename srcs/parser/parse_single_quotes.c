/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:26 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/06 15:24:26 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*set_cmd(t_parser *p, t_AST *last)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	token = eat(p, SIMPLE_QUOTE_TOKEN);
	if (!token)
		return (NULL);
	if (last->e_type == PROGRAM)
	{
		cmd = init_cmd(token->value);
		list_push(cmd->argv, token->value);
		addback_AST(&last, init_AST(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)last->body;
		list_push(cmd->argv, token->value);
	}
	free(token);
	return (cmd);
}

void	parse_single_quotes(t_parser *p, t_AST *ast)
{
	t_cmd	*cmd;
	t_AST	*last;

	if (p->token->e_type != SIMPLE_QUOTE_TOKEN)
		return ;
	last = get_last(&ast);
	cmd = NULL;
	if (last->e_type != PROGRAM)
		cmd = (t_cmd *)last->body;
	cmd = set_cmd(p, last);
	if (!cmd)
		return ;
	eat_words(p, cmd);
	parse_single_quotes(p, ast);
}
