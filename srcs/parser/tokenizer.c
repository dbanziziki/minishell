#include "tokenizer.h"
#include "libft.h"

t_tokenizer *init_tokenizer(char *str)
{
	t_tokenizer *new;

	new = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (!new)
		return (NULL);
	new->len = ft_strlen(str);
	new->str = str;
	new->cursor = 0;
	return (new);
}

int	has_more_tokens(t_tokenizer *t)
{
	return (t->cursor < t->len);
}

t_token	*new_token(int type, char *value)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	return (new);
}

t_token	*word_token(t_tokenizer *t, char *temp)
{
	size_t	i;
	t_token	*token;

	i = t->cursor;
	while (t->str[t->cursor] && t->str[t->cursor] != ' ' &&
			t->str[t->cursor] != PIPE_TOKEN &&
			t->str[t->cursor] != '<' &&
			t->str[t->cursor] != '>' &&
			t->str[t->cursor] != '|')
			t->cursor++;
	token = new_token(WORD_TOKEN, ft_strndup(temp, t->cursor - i));
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

t_token	*double_redirect_token(t_tokenizer *t, char *temp, int type)
{
	t_token	*token;

	token = new_token(type, ft_strndup(temp, 2));
	if (!token)
		return (NULL);
	t->cursor += 2;
	return (token);
}

t_token	*dollarsign_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	size_t	i;

	i = t->cursor;
	while (t->str[t->cursor] && t->str[t->cursor] != ' ')
		t->cursor++;
	token = new_token(DOLLARSIGN_TOKEN, ft_strndup(temp, t->cursor - i));
	if (!token)
		return (NULL);
	return (token);
}

t_token	*quote_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	size_t	i;
	int		type;

	if (temp[0] == DOUBLE_QUOTE_TOKEN)
		type = DOUBLE_QUOTE_TOKEN;
	else
		type = SIMPLE_QUOTE_TOKEN;
	i = t->cursor;
	t->cursor++;
	while (t->str[t->cursor] && t->str[t->cursor] != type)
		t->cursor++;
	token = new_token(type, ft_strndup(temp, (t->cursor + 1) - i));
	t->cursor++;
	if (!token)
		return (NULL);
	return (token);
}

char	*skip_whitespace(char *str, t_tokenizer *t)
{
	if (!str)
		return (str);
	while (t->str[t->cursor] == ' ')
			t->cursor++;
		str = &(t->str[t->cursor]);
	return (str);
}

t_token	*get_next_token(t_tokenizer *t)
{
	char		*temp;
	t_token		*token;
	
	temp = skip_whitespace(&(t->str[t->cursor]), t);
	token = NULL;
	if (temp)
	{
		if (ft_isalpha(temp[0]) || temp[0] == '-' || temp[0] == '.')
			return (word_token(t, temp));
		else if (temp[0] == PIPE)
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
			return (new_token(EOF_TOKEN, ft_strndup("EOF", 3)));
		else
			return (new_token(UNKNOWN_TOKEN, ft_strndup(temp, 1)));
	}
	return (token);
}

