#include "tokenizer.h"
#include "minishell.h"

static void	update_quote_value(t_tokenizer *t, t_quote *q, int i)
{
	char	*temp_val;
	char	*temp;
	char	*temp_dup;

	q->len = 0;
	while (t->str[t->cursor] && t->str[t->cursor] != q->type)
	{
		q->len++;
		t->cursor++;
	}
	temp_val = q->val;
	temp_dup = ft_strndup(&t->str[i], q->len);
	if (!temp_dup)
		return ;
	if (*temp_dup == '$' && q->type == DOUBLE_QUOTE)
	{
		temp = temp_dup;
		temp_dup = ft_strdup(get_env_v(temp + 1, t->envp));
		free(temp);
	}
	q->val = ft_strjoin_free_both(q->val, temp_dup);
	if (t->str[t->cursor] != q->type)
		q->con = 0;
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

void	parse_again(t_tokenizer *t, t_quote *q)
{
	char	*temp_val;
	int		i;
	t_token	*token;

	i = t->cursor;
	if (!ft_isspace(t->str[t->cursor]) && t->str[t->cursor]
		&& t->str[t->cursor] != q->other)
		update_quote_value(t, q, i);
	else if (t->str[t->cursor] == q->other) //:TODO
	{
		printf("doing some stuff %s\n", &t->str[t->cursor]);
		/*token = single_quote_token(t);
		if (!token)
			return ;
		temp_val = q->val;
		q->val = ft_strjoin_free_both(temp_val, token->value);
		free(token);
		if (t->str[t->cursor] != DOUBLE_QUOTE)
			q->con = 0;*/
	}
	else
		q->con = 0;
}
