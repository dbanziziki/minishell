/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:19 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:52:32 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*create_cmd(t_ast *last, t_token *token)
{
	char	*parsed;
	t_cmd	*cmd;

	cmd = NULL;
	parsed = ft_strdup(token->value);
	if (last->e_type == PROGRAM)
	{
		cmd = init_cmd(parsed);
		list_push(cmd->argv, parsed);
		addback_ast(&last, init_ast(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)last->body;
		list_push(cmd->argv, parsed);
	}
	return (cmd);
}

static t_cmd	*set_cmd(t_parser *p, t_ast *last)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	token = eat(p, DOUBLE_QUOTE_TOKEN);
	if (!token)
		return (NULL);
	cmd = create_cmd(last, token);
	free(token->value);
	free(token);
	return (cmd);
}

void	parse_double_quotes(t_parser *p, t_ast *ast)
{
	t_cmd	*cmd;
	t_ast	*last;

	if (!p->token)
	{
		p->flag = 1;
		return ;
	}
	if (p->token->e_type != DOUBLE_QUOTE_TOKEN)
		return ;
	last = get_last(&ast);
	cmd = NULL;
	if (last->e_type != PROGRAM)
		cmd = (t_cmd *)last->body;
	cmd = set_cmd(p, last);
	if (!cmd)
		return ;
	eat_words(p, cmd);
	parse_double_quotes(p, ast);
}
