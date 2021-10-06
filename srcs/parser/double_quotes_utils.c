/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:19:26 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/06 15:19:27 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "tokenizer.h"
#include "minishell.h"

static void	set_new_quote_value(t_tokenizer *t, t_quote *q, char *temp_dup)
{
	char	*temp;

	if (*temp_dup == '$' && q->type == DOUBLE_QUOTE)
	{
		temp = temp_dup;
		temp_dup = ft_strdup(get_env_v(temp + 1, t->envp));
		free(temp);
	}
	if (!q->val)
		q->val = temp_dup;
	else
		q->val = ft_strjoin_free_both(q->val, temp_dup);
	if (ft_isspace(t->str[t->cursor]))
		q->con = 0;
}

static void	update_quote_value(t_tokenizer *t, t_quote *q, int i)
{
	char	*temp;
	char	*temp_dup;

	q->len = 0;
	while (t->str[t->cursor] && t->str[t->cursor] != q->type
		&& t->str[t->cursor] != q->other)
	{
		q->len++;
		t->cursor++;
	}
	temp_dup = ft_strndup(&t->str[i], q->len);
	if (!temp_dup)
		return ;
	set_new_quote_value(t, q, temp_dup);
}

void	join_token_value(t_tokenizer *t, t_quote *q, int i)
{
	char	*temp;
	char	*temp_dup;
	char	*other;

	temp = q->val;
	temp_dup = ft_strndup(&t->str[i], q->len);
	if (!temp_dup)
		return ;
	if (*temp_dup == '$' && q->type == DOUBLE_QUOTE)
	{
		other = temp_dup;
		temp_dup = ft_strdup(get_env_v(temp_dup + 1, t->envp));
		q->val = ft_strjoin_free_both(temp, temp_dup);
		free(other);
		if (!q->val)
			return ;
	}
	else
	{
		q->val = ft_strjoin_free_both(temp, temp_dup);
		if (!q->val)
			return ;
	}
}

static int	parse_other(t_tokenizer *t, t_quote *q)
{
	t_token	*token;
	char	*temp_val;

	token = quote_token(t, q->other, q->type);
	if (!token)
		return (0);
	temp_val = q->val;
	if (!temp_val)
		q->val = token->value;
	else
	{
		if (token->value)
			q->val = ft_strjoin_free_both(temp_val, token->value);
		else
			q->val = temp_val;
	}
	free(token);
	if (t->str[t->cursor] != q->type)
		q->con = 0;
	return (1);
}

int	parse_again(t_tokenizer *t, t_quote *q)
{
	int		i;

	i = t->cursor;
	if (!ft_isspace(t->str[t->cursor]) && t->str[t->cursor]
		&& t->str[t->cursor] != q->other)
		update_quote_value(t, q, i);
	else if (t->str[t->cursor] == q->other)
	{
		if (!parse_other(t, q))
			return (0);
	}
	else
		q->con = 0;
	return (1);
}
