#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unistd.h>
#include <stdlib.h>

typedef enum e_states t_type;


typedef struct s_token
{
	enum
	{
		WORD,
		REDIRECT,
		UNKNOWN,
		HEREDOC,
		EOF_TOKEN,
		WHITE_SPACE = ' ',
		PIPE = '|',
		DOUBLE_QUOTE = '"',
		SIMPLE_QUOTE = '\'',
		DOLLARSIGN = '$'
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

#endif
