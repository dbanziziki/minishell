#include "tokenizer.h"

static int	advence_cursor(t_tokenizer *t, int type)
{
    int start;
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
    return (start);
}

t_token	*quote_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	size_t	i;
	int		type;
    int     start;

	if (temp[0] == DOUBLE_QUOTE)
		type = DOUBLE_QUOTE_TOKEN;
	else
		type = SIMPLE_QUOTE_TOKEN;
	i = t->cursor;
	t->cursor++;
    if (type == DOUBLE_QUOTE_TOKEN)
    {
        while (t->str[t->cursor] == DOUBLE_QUOTE)
            t->cursor++;
    }
    else
    {
        while (t->str[t->cursor] == SINGLE_QUOTE)
            t->cursor++;
    }
	//start = advence_cursor(t, type);
	token = new_token(type, ft_strndup(&t->str[t->cursor], (t->cursor - 1) - i));
	if (t->cursor < t->len)
		t->cursor++;
	if (!token)
		return (NULL);
	return (token);
}