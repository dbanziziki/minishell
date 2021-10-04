#include "tokenizer.h"
#include "minishell.h"
//""'"hello"'""

void	full_str(t_tokenizer *t, t_quote *q)
{
	int		len;
	int		i;
	char	*temp;
	char	*temp_dup;

	len = 0;
	while (t->str[t->cursor] && t->str[t->cursor] == DOUBLE_QUOTE)
	{
		q->open++;
		t->cursor++;
	}
	i = t->cursor;
	while (t->str[t->cursor] && t->str[t->cursor] != DOUBLE_QUOTE)
	{
		t->cursor++;
		len++;
	}
	if (!q->val)
	{
		q->val = ft_strndup(&t->str[i], len);
		if (*(q->val) == '$')
		{
			temp = q->val;
			q->val = ft_strdup(get_env_v(temp + 1, t->envp));
			free(temp);
		}	
	}
	else
	{
		temp = q->val;
		temp_dup = ft_strndup(&t->str[i], len);
		if (*temp_dup == '$')
		{
			char *other = temp_dup;
			temp_dup = get_env_v(temp_dup + 1, t->envp);
			free(other);
		}
		q->val = ft_strjoin(temp, temp_dup);
		free(temp);
		free(temp_dup);
	}
	if (t->str[t->cursor] == DOUBLE_QUOTE)
		q->close = 1;
	else
		q->close = 0;
}

static void	parse_again(t_tokenizer *t, t_quote *q)
{
	int		len;
	char	*temp_val;
	char	*temp_dup;
	int		i;

	if (t->str[t->cursor] == DOUBLE_QUOTE)
	{
		t->cursor += q->open;
		i = t->cursor;
		if (!ft_isspace(t->str[t->cursor]) && t->str[t->cursor])
		{
			len = 0;
			while (t->str[t->cursor] && t->str[t->cursor] != DOUBLE_QUOTE)
			{
				len++;
				t->cursor++;
			}
			temp_val = q->val;
			temp_dup = ft_strndup(&t->str[i], len);
			q->val = ft_strjoin(q->val, temp_dup);
			free(temp_val);
			free(temp_dup);
			if (t->str[t->cursor] != DOUBLE_QUOTE)
				q->con = 0;
		}
		else
			q->con = 0;
	}
}

t_token	*quote_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	t_quote	q;

	(void)temp;
	token = NULL;
	ft_memset(&q, 0, sizeof(t_quote));
	q.close = 1;
	q.con = 1;
	while (q.con && q.close)
	{
		q.open = 0;
		full_str(t, &q);
		if (!q.close)
			printf("error not closed\n");
		else
			printf("closed quotes\n");
		//check if closed
		parse_again(t, &q);
	}
	token = new_token(DOUBLE_QUOTE_TOKEN, q.val);
	return (token);
}