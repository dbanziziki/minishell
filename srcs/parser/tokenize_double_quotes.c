#include "tokenizer.h"
#include "minishell.h"
//""'"hello"'""

static int	update_vals(t_tokenizer *t, t_quote *q, int c)
{
	int	i;

	q->len = 0;
	if (t->str[t->cursor] == c)
	{
		t->cursor++;
		q->open = 1;
	}
	else //shound be an error?
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
	if (*(q->val) == '$' && q->type == DOUBLE_QUOTE)
	{
		temp = q->val;
		q->val = ft_strdup(get_env_v(temp + 1, t->envp));
		free(temp);
	}
}

static void	togle_open_close(t_quote *q, int o, int c)
{
	q->close = c;
	q->open = o;
}

static void	full_str(t_tokenizer *t, t_quote *q)
{
	int		i;
	char	*temp;
	char	*temp_dup;

	
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
	else //TODO
	{
		printf("causes the error\n");
		togle_open_close(q, 1, 0);
	}
}

t_token	*quote_token(t_tokenizer *t, int c, int other)
{
	t_token	*token;
	t_quote	q;

	token = NULL;
	ft_memset(&q, 0, sizeof(t_quote));
	q.close = 1;
	q.con = 1;
	q.type = c;
	q.other = other;
	while (q.con && q.close && t->str[t->cursor])
	{
		q.open = 0;
		full_str(t, &q);
		if (!q.close)
		{
			printf("ERROR\n");
			free(q.val);
			return (NULL);
		}
		parse_again(t, &q);
	}
	token = new_token(DOUBLE_QUOTE_TOKEN, q.val);
	return (token);
}