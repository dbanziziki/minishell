#include "tokenizer.h"

t_tokenizer	*init_tokenizer(char *str)
{
	t_tokenizer	*new;

	new = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (!new)
		return (NULL);
	new->len = ft_strlen(str);
	new->str = str;
	new->cursor = 0;
	return (new);
}

t_token	*word_token(t_tokenizer *t, char *temp)
{
	size_t	i;
	t_token	*token;

	i = t->cursor;
	while (t->str[t->cursor] && !ft_isspace(t->str[t->cursor])
		&& t->str[t->cursor] != '<'
		&& t->str[t->cursor] != '>'
		&& t->str[t->cursor] != '|')
		t->cursor++;
	token = new_token(WORD_TOKEN, ft_strndup(temp, t->cursor - i));
	if (!token)
		return (NULL);
	return (token);
}

t_token	*double_redirect_token(t_tokenizer *t, char *temp, int type)
{
	t_token	*token;

	token = new_token(type, ft_strndup(temp, 2));
	if (!token)
		return (NULL);
	t->cursor += 2;
	return (token);
}

static t_token	*switch_token(t_tokenizer *t, char *temp)
{
	if (temp[0] == PIPE)
		return (simple_token(t, temp));
	else if (!ft_strncmp(temp, HEREDOC, 2))
		return (double_redirect_token(t, temp, HEREDOC_TOKEN));
	else if (!ft_strncmp(temp, REDIRECT_APPEND, 2))
		return (double_redirect_token(t, temp, GGREATER_THAN_TOKEN));
	else if (temp[0] == LEFT_REDIRECT || temp[0] == RIGHT_REDIRECT)
		return (simple_token(t, temp));
	else if (temp[0] == DOLLARSIGN)
		return (dollarsign_token(t, temp));
	else if (temp[0] == DOUBLE_QUOTE || temp[0] == SINGLE_QUOTE)
		return (quote_token(t, temp));
	else if (!temp[0])
		return (new_token(EOF_TOKEN, ft_strndup("NULL", 4)));
	else
		return (word_token(t, temp));
}

t_token	*get_next_token(t_tokenizer *t)
{
	char		*temp;
	t_token		*token;

	temp = skip_whitespace(&(t->str[t->cursor]), t);
	token = NULL;
	if (temp)
		return (switch_token(t, temp));
	return (token);
}
