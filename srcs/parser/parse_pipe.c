/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:14 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:14:37 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	update_prog(t_program **prog)
{
	if (!prog)
		return ;
	(*prog)->has_pipes = 1;
	(*prog)->nb_pipes++;
}

static t_cmd	*set_pipe_cmd(t_parser *p)
{
	t_cmd	*cmd;
	t_token	*token;

	if (p->token->e_type != WORD_TOKEN)
		return (init_cmd(NULL));
	token = eat(p, WORD_TOKEN);
	if (!token)
		return (NULL);
	cmd = init_cmd(token->value);
	list_push(cmd->argv, token->value);
	free(token);
	eat_words(p, cmd);
	return (cmd);
}

t_ast	*parse_pipe(t_parser *p, t_ast *ast)
{
	t_token		*token;
	t_cmd		*cmd;
	t_program	*prog;
	t_ast		*last;

	last = get_last(&ast);
	token = eat(p, PIPE_TOKEN);
	if (!token)
		return (NULL);
	if (last->e_type == PROGRAM)
	{
		print_error("minishell: parse error near ", token->value);
		free(token->value);
		free(token);
		p->flag = 1;
		return (NULL);
	}
	prog = (t_program *)ast->body;
	update_prog(&prog);
	free(token->value);
	free(token);
	cmd = set_pipe_cmd(p);
	return (init_ast(PIPE_CMD_AND_ARG, cmd));
}
