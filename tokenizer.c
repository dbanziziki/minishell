#include "tokenizer.h"
#include <stdio.h>
#include "utils.h"

t_tokenizer *init(char *str)
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

t_token	*new_token(t_type type, char *value)
{
	t_token *new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	return (new);
}

t_token	*get_next_token(t_tokenizer *t)
{
	char		*temp;
	t_token		*token;
	size_t		i;
	
	token = NULL;
	if (!has_more_tokens(t))
		return (NULL);
	printf("cursor [%lu]\n", t->cursor);
	temp = &(t->str[t->cursor]);
	if (temp[0] == ' ')
	{
		while (t->str[t->cursor] == ' ')
			t->cursor++;
		temp = &(t->str[t->cursor]);
	}
	printf("%s\n", temp);
	i = t->cursor;
	if (ft_isalpha(temp[0]))
	{
		while (ft_isalpha(t->str[t->cursor]))
			t->cursor++;
		token = new_token(WORD, ft_strndup(temp, t->cursor - i));
	}
	else
	{
		printf("unkwon token\n");
		return (NULL);
	}
	return (token);
}

/*int main(int argc, char const *argv[])
{
	t_tokenizer	*t;
	t_token		*token;

	t = init("cat ");
	token = get_next_token(t);
	printf("%s - %d\n", token->value, t->cursor);
	free(t);
	free(token->value);
	free(token);
	return 0;
}*/
