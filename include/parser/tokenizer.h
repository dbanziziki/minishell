#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unistd.h>
#include <stdlib.h>
#include "tokens.h"
#include "utils.h"
#include "libft.h"

typedef struct s_token
{
	enum
	{
		WORD_TOKEN,
		REDIRECT_TOKEN,
		GREATER_THAN_TOKEN,
		LESS_THAN_TOKEN,
		UNKNOWN_TOKEN,
		HEREDOC_TOKEN,
		EOF_TOKEN,
		WHITE_SPACE_TOKEN,
		PIPE_TOKEN,
		DOUBLE_QUOTE_TOKEN,
		SIMPLE_QUOTE_TOKEN,
		DOLLARSIGN_TOKEN
	}			type;
	char		*value;
}				t_token;

typedef struct s_tokenizer
{
	char				*str;
	size_t				len;
	size_t				cursor;
}						t_tokenizer;

t_tokenizer	*init_tokenizer(char *str);
t_token		*get_next_token(t_tokenizer *t);
t_token		*new_token(int type, char *value);
int			has_more_tokens(t_tokenizer *t);
char		*token_to_str(int token);

#endif
