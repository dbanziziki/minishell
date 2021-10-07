/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:29 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:14:58 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*set_cmd(t_parser *p, t_ast *last)
{
	t_cmd	*cmd;
	t_token	*token;

	token = eat(p, WORD_TOKEN);
	if (!token)
		return (NULL);
	if (last->e_type != PROGRAM)
	{
		cmd = (t_cmd *)last->body;
		if (!cmd->cmd)
			cmd->cmd = token->value;
	}
	else
		cmd = init_cmd(token->value);
	list_push(cmd->argv, token->value);
	free(token);
	return (cmd);
}

int	parse_word(t_parser *p, t_ast *ast)
{
	t_cmd	*cmd;
	t_ast	*last;

	last = get_last(&ast);
	cmd = set_cmd(p, last);
	if (!cmd)
		return (-1);
	eat_words(p, cmd);
	if (last->e_type == PROGRAM)
		addback_ast(&ast, init_ast(CMD_AND_ARG, cmd));
	return (1);
}
