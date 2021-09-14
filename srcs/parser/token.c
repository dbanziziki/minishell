#include "tokenizer.h"

t_token	*new_token(int type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	return (new);
}
