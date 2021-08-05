#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <unistd.h>
#include <stdlib.h>

typedef enum e_states t_type;

enum e_states
{
	WORD,
	REDIRECT,
	UNKNOWN,
	HEREDOC,
	PROGRAM,
	WHITE_SPACE = ' ',
	PIPE = '|',
	DOUBLE_QUOTE = '"',
	SIMPLE_QUOTE = '\'',
	DOLLARSIGN = '$'
};

typedef struct s_token
{
	t_type		type;
	char		*value;
}				t_token;

typedef struct s_tokenizer
{
	char				*str;
	size_t				len;
	int					cursor;
}						t_tokenizer;

t_tokenizer	*init(char *str);
t_token		*get_next_token(t_tokenizer *t);

#endif