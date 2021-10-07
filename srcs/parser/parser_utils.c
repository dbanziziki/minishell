/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:32 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 11:50:22 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	eat_words(t_parser *p, t_cmd *cmd)
{
	t_token	*token;

	token = NULL;
	if (!p->token)
	{
		p->flag = 1;
		return ;
	}
	while (p->token->e_type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		if (!token)
			return ;
		list_push(cmd->argv, token->value);
		free(token);
		token = NULL;
	}
}

t_cmd	*init_cmd(char *value)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = value;
	cmd->argv = init_list(sizeof(char *));
	cmd->io_mod = 0;
	cmd->proc_idx = 0;
	cmd->hd = 0;
	return (cmd);
}

t_io_mod	*init_io_mod(int type)
{
	t_io_mod	*io_mod;

	io_mod = (t_io_mod *)malloc(sizeof(t_io_mod));
	if (!io_mod)
		return (NULL);
	io_mod->e_type = type;
	io_mod->infile = NULL;
	io_mod->hd_flag = 0;
	io_mod->out = init_list(sizeof(char *));
	return (io_mod);
}

t_parser	*init_parser(char *str)
{
	t_tokenizer	*t;
	t_parser	*p;

	t = init_tokenizer(str);
	if (!t)
		return (NULL);
	p = (t_parser *)malloc(sizeof(t_parser));
	if (!t)
		return (NULL);
	p->t = t;
	p->flag = 0;
	p->hd_err = 0;
	p->token = get_next_token(t);
	p->var = 0;
	return (p);
}
