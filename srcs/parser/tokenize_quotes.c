/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:19:41 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/07 13:22:22 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "minishell.h"

static int	update_vals(t_tokenizer *t, t_quote *q, int c)
{
	int	i;

	q->len = 0;
	if (t->str[t->cursor] == c)
	{
		t->cursor++;
		q->open = 1;
	}
	else
		return (0);
	i = t->cursor;
	while (t->str[t->cursor] && t->str[t->cursor] != c)
	{
		t->cursor++;
		q->len++;
	}
	return (i);
}

static void	set_token_value(t_tokenizer *t, t_quote *q, int i)
{
	char	*temp;

	q->val = ft_strndup(&t->str[i], q->len);
	if (!q->val)
	{
		q->con = 0;
		return ;
	}
	if (q->type == DOUBLE_QUOTE)
	{
		temp = q->val;
		q->val = parse_str(q->val, t->envp);
	}
}

static void	full_str(t_tokenizer *t, t_quote *q)
{
	int		i;

	i = update_vals(t, q, q->type);
	if (q->len)
	{
		if (!q->val)
			set_token_value(t, q, i);
		else
			join_token_value(t, q, i);
	}
	if (t->str[t->cursor] == q->type)
	{
		t->cursor++;
		togle_open_close(q, 0, 1);
	}
	else if (t->str[t->cursor] == q->other)
		togle_open_close(q, 1, 1);
	else
		togle_open_close(q, 1, 0);
}

static int	parse_token_val(t_tokenizer *t, t_quote *q)
{
	q->open = 0;
	full_str(t, q);
	if (!q->close)
	{
		free(q->val);
		return (0);
	}
	if (!parse_again(t, q))
	{
		if (q->val)
			free(q->val);
		return (0);
	}
	return (1);
}

t_token	*quote_token(t_tokenizer *t, int c, int other)
{
	t_token	*token;
	t_quote	q;

	ft_memset(&q, 0, sizeof(t_quote));
	q.close = 1;
	q.con = 1;
	q.type = c;
	q.other = other;
	while (q.con && q.close && t->str[t->cursor])
	{
		if (!parse_token_val(t, &q))
			return (NULL);
	}
	if (q.type == DOUBLE_QUOTE)
		token = new_token(DOUBLE_QUOTE_TOKEN, q.val);
	else
		token = new_token(SIMPLE_QUOTE_TOKEN, q.val);
	return (token);
}
