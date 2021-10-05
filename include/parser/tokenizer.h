#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <unistd.h>
# include <stdlib.h>
# include "tokens.h"
# include "list.h"
# include "utils.h"
# include "libft.h"

typedef struct s_quote	t_quote;

typedef struct s_token
{
	enum
	{
		WORD_TOKEN,
		GGREATER_THAN_TOKEN,
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
	}			e_type;
	char		*value;
}				t_token;

struct s_quote
{
	int		open;
	int		con;
	int		len;
	int		close;
	char	*val;
};

typedef struct s_tokenizer
{
	t_array				*envp;
	char				*str;
	size_t				len;
	size_t				cursor;
}						t_tokenizer;

t_tokenizer	*init_tokenizer(char *str);
t_token		*get_next_token(t_tokenizer *t);
t_token		*new_token(int type, char *value);
t_token		*single_quote_token(t_tokenizer *t);
t_token		*quote_token(t_tokenizer *t);
t_token		*word_token(t_tokenizer *t, char *temp);
char		*skip_whitespace(char *str, t_tokenizer *t);
t_token		*dollarsign_token(t_tokenizer *t, char *temp);
t_token		*simple_token(t_tokenizer *t, char *temp);
void		parse_again(t_tokenizer *t, t_quote *q);
void		join_token_value(t_tokenizer *t, t_quote *q, int i);
#endif
