#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "AST.h"
# include "list.h"
# include "utils.h"
# include "libft.h"

typedef struct s_io_modifier
{
	enum
	{
		REDIRECT_OUTPUT,
		REDIRECT_OUTPUT_APPEND,
		REDIRECT_INPUT,
		REDIRECT_INPUT_OUTPUT,
		REDIRECT_INPUT_OUTPUT_APPEND
	}			type;
	char		*infile;
	t_array		*out;
	int			fds[2];
}				t_io_mod;

typedef struct s_cmd
{
	int			proc_idx;
	char		*cmd;
	t_array		*argv;
	t_io_mod	*io_mod;
	t_list		*hd;
}				t_cmd;

typedef struct s_parser
{
	int			flag;
	t_tokenizer	*t;
	t_token		*token;
	t_array		*var;
}				t_parser;

t_parser	*init_parser(char *str);
t_token		*eat(t_parser *p, int type);
int			parse_word(t_parser *p, t_AST *ast);
int			parse(t_parser *p, t_AST **ast);
t_AST		*parse_pipe(t_parser *p, t_AST *ast);
t_cmd		*init_cmd(char *value);
t_io_mod	*init_io_mod(int type);
void		parse_redirections(t_parser *p, t_AST *ast);
void		parse_double_quotes(t_parser *p, t_AST *ast);
void		parse_single_quotes(t_parser *p, t_AST *ast);
void		eat_words(t_parser *p, t_cmd *cmd);
char		*parse_str(char *str, t_array *var);
void		parse_env_var(t_parser *p, t_AST *ast);
void		parse_heredoc(t_parser *p, t_AST *ast);
#endif
