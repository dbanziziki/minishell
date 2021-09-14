#include "tokenizer.h"

static void	advence_cursor(t_tokenizer *t, int type)
{
	if (!t)
		return ;
	if (type == DOUBLE_QUOTE_TOKEN)
	{
		while (t->str[t->cursor] && t->str[t->cursor] != DOUBLE_QUOTE)
			t->cursor++;
	}
	else
	{
		while (t->str[t->cursor] && t->str[t->cursor] != SINGLE_QUOTE)
			t->cursor++;
	}
}

t_token	*quote_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	size_t	i;
	int		type;

	if (temp[0] == DOUBLE_QUOTE)
		type = DOUBLE_QUOTE_TOKEN;
	else
		type = SIMPLE_QUOTE_TOKEN;
	i = t->cursor;
	t->cursor++;
	advence_cursor(t, type);
	token = new_token(type, ft_strndup(++temp, (t->cursor - 1) - i));
	if (t->cursor < t->len)
		t->cursor++;
	if (!token)
		return (NULL);
	return (token);
}

char	*skip_whitespace(char *str, t_tokenizer *t)
{
	if (!str)
		return (str);
	while (t->str[t->cursor] && ft_isspace(t->str[t->cursor]))
		t->cursor++;
	str = &(t->str[t->cursor]);
	return (str);
}

t_token	*dollarsign_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	size_t	i;

	i = t->cursor;
	if (!temp[1] || ft_isspace(temp[1]))
	{
		t->cursor++;
		return (new_token(WORD_TOKEN, ft_strndup(temp, 1)));
	}
	while (t->str[t->cursor] && t->str[t->cursor] != ' ')
		t->cursor++;
	token = new_token(DOLLARSIGN_TOKEN, ft_strndup(temp, t->cursor - i));
	if (!token)
		return (NULL);
	return (token);
}

t_token	*simple_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	int		type;

	if (temp[0] == LEFT_REDIRECT)
		type = LESS_THAN_TOKEN;
	else if (temp[0] == RIGHT_REDIRECT)
		type = GREATER_THAN_TOKEN;
	else
		type = PIPE_TOKEN;
	token = new_token(type, ft_strndup(temp, 1));
	if (!token)
		return (NULL);
	t->cursor++;
	return (token);
}
