#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "AST.h"
#include "list.h"
#include "utils.h"
#include "libft.h"

typedef struct s_io_modifier
{
	enum
	{
		NONE,
		REDIRECT_OUTPUT,
		REDIRECT_OUTPUT_APPEND,
		REDIRECT_INPUT,
		REDIRECT_INPUT_OUTPUT,
	}			type;
	char		*infile;
	char		*outfile;
	int			fds[2]; /* fd[0] = infile fd[1] = outfile */
}				t_io_mod;

typedef struct s_cmd
{
	int			proc_idx;
	char 		*cmd;
	t_array		*argv;
	t_io_mod	*io_mod;
} 				t_cmd;

typedef struct s_parser
{
	t_tokenizer	*t;
	t_token 	*token;
}				t_parser;

t_parser	*init_parser(char *str);
t_token		*eat(t_parser *p, int type);
t_AST		*parse_word(t_parser *p);
t_AST		*parse(t_parser *p, t_AST *ast);
t_AST		*parse_pipe(t_parser *p, t_AST *ast);
t_cmd   	*init_cmd(char *value);
t_io_mod    *init_io_mod(char *infile, char *outfile, int type);
void		parse_redirection(t_parser *p, t_AST *ast);
void		parse_double_quotes(t_parser *p, t_AST *ast);
#endif
