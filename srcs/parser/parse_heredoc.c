/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:11 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:14:58 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	set_cmd_and_arg(t_parser *p, t_ast **ast, t_list *hd)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	if (p->token->e_type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		cmd = init_cmd(token->value);
		list_push(cmd->argv, token->value);
		free(token);
		eat_words(p, cmd);
		cmd->hd = hd;
	}
	else
	{
		cmd = init_cmd(NULL);
		cmd->hd = hd;
	}
	if (cmd->io_mod)
		cmd->io_mod->hd_flag = 1;
	addback_ast(ast, init_ast(CMD_AND_ARG, cmd));
}

static void	push_hd(t_parser *p, t_ast *last, t_cmd *cmd, t_token *token)
{
	t_list	*hd;

	hd = NULL;
	if (!token)
		return ;
	if (cmd && cmd->hd)
		ft_lstadd_back(&(cmd->hd), ft_lstnew(token->value));
	else
		ft_lstadd_back(&hd, ft_lstnew(token->value));
	free(token);
	if (cmd == NULL)
		set_cmd_and_arg(p, &last, hd);
	else
	{
		if (cmd->io_mod)
			cmd->io_mod->hd_flag = 1;
		ft_lstadd_back(&(cmd->hd), hd);
	}
}

static void	set_heredoc(t_parser *p, t_ast *last, t_cmd *cmd)
{
	t_token	*token;

	if (p->token->e_type == WORD_TOKEN)
		token = eat(p, WORD_TOKEN);
	else
	{
		token = eat(p, EOF_TOKEN);
		p->hd_err = 1;
	}
	if (!token)
		return ;
	push_hd(p, last, cmd, token);
}

void	parse_heredoc(t_parser *p, t_ast *ast)
{
	t_token		*token;
	t_list		*hd;
	t_ast		*last;
	t_cmd		*cmd;

	if (p->token->e_type != HEREDOC_TOKEN)
		return ;
	last = get_last(&ast);
	hd = NULL;
	cmd = NULL;
	if (last->e_type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, HEREDOC_TOKEN);
	if (!token)
		return ;
	free(token->value);
	free(token);
	set_heredoc(p, last, cmd);
}
