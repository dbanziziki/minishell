#ifndef PARSER_H
#define PARSER_H

#include "tokenizer.h"
#include "AST.h"
#include "list.h"
#include "utils.h"

typedef struct s_io_modifier
{
	enum
	{
		NONE,
		REDIRECT_OUTPUT,
		REDIRECT_INPUT
	}			type;
	char		*infile;
	char		*oufile;
}				t_io_mod;

typedef struct s_cmd
{
	char 		*cmd;
	t_list		*argv;
	t_io_mod	*io_mod;
} 				t_cmd;

typedef struct s_pipe
{
	/*can ether be t_cmd or ??? */
	void	*body;
}				t_pipe;

typedef struct s_parser
{
	t_tokenizer	*t;
	t_token 	*token;
}				t_parser;

t_parser	*init_parser(char *str);
t_token		*eat(t_parser *p, int type);
t_AST		*parse_word(t_parser *p);
t_AST		*parse(t_parser *p, t_AST *ast);
t_AST		*parse_pipe(t_parser *p);
t_cmd   	*init_cmd(char *value);
t_io_mod    *init_io_mod(char *infile, char *outfile, int type);
#endif
