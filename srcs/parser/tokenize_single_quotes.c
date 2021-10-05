#include "tokenizer.h"

static int	update_vals(t_tokenizer *t, t_quote *q)
{
	int	i;

	q->len = 0;
	while (t->str[t->cursor] && t->str[t->cursor] == SINGLE_QUOTE)
	{
		q->open++;
		t->cursor++;
	}
	i = t->cursor;
	while (t->str[t->cursor] && t->str[t->cursor] != SINGLE_QUOTE)
	{
		t->cursor++;
		q->len++;
	}
	return (i);
}

static void	set_token_value(t_tokenizer *t, t_quote *q, int i)
{
	q->val = ft_strndup(&t->str[i], q->len);
	if (!q->val)
	{
		q->con = 0;
		return ;
	}
}

static void	join_token_value(t_tokenizer *t, t_quote *q, int i)
{
	char	*temp;
	char	*temp_dup;

	temp = q->val;
	temp_dup = ft_strndup(&t->str[i], q->len);
    q->val = ft_strjoin(temp, temp_dup);
    if (!q->val)
        return ;
    free(temp);
    free(temp_dup);
}

static void	full_str(t_tokenizer *t, t_quote *q)
{
	int		i;
	char	*temp;
	char	*temp_dup;

	
	i = update_vals(t, q);
	if (!q->val)
		set_token_value(t, q, i);	
	else
		join_token_value(t, q, i);
	if (t->str[t->cursor] == SINGLE_QUOTE)
		q->close = 1;
	else
		q->close = 0;
}

static void	update_token_value(t_tokenizer *t, t_quote *q)
{
	char	*temp_val;
	char	*temp_dup;
	int		i;

	t->cursor += q->open;
	i = t->cursor;
	if (!ft_isspace(t->str[t->cursor]) && t->str[t->cursor]
		&& t->str[t->cursor] != DOUBLE_QUOTE)
	{
		q->len = 0;
		while (t->str[t->cursor] && t->str[t->cursor] != SINGLE_QUOTE)
		{
			q->len++;
			t->cursor++;
		}
		temp_val = q->val;
		temp_dup = ft_strndup(&t->str[i], q->len);
		q->val = ft_strjoin(q->val, temp_dup);
		free(temp_val);
		free(temp_dup);
		if (t->str[t->cursor] != SINGLE_QUOTE)
			q->con = 0;
	}
	else if (t->str[t->cursor] == DOUBLE_QUOTE)
		quote_token(t);
	else
		q->con = 0;
}

static void	parse_again_s(t_tokenizer *t, t_quote *q)
{
	int		len;

	if (t->str[t->cursor] == SINGLE_QUOTE)
		update_token_value(t, q);
}

t_token	*single_quote_token(t_tokenizer *t)
{
	t_token	*token;
	t_quote	q;

	token = NULL;
	ft_memset(&q, 0, sizeof(t_quote));
	q.close = 1;
	q.con = 1;
	while (q.con && q.close)
	{
		q.open = 0;
		full_str(t, &q);
		if (!q.close)
		{
			free(q.val);
			return (NULL);
		}
		parse_again_s(t, &q);
	}
	token = new_token(SIMPLE_QUOTE_TOKEN, q.val);
	return (token);
}