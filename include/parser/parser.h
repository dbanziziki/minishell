#ifndef PARSER_H
# define PARSER_H

#include "tokenizer.h"
#include "AST.h"
#include "list.h"
#include "utils.h"

typedef struct s_cmd
{
    char    *cmd;
    t_list    *argv;
}               t_cmd;


typedef struct s_parser
{
    t_tokenizer *t;
    t_token     *token;
}               t_parser;

t_parser	*init_parser(char *str);
t_token		*eat(t_parser *p, int type);
t_AST       *word(t_token *curr_token, t_parser *p);
t_AST	    *parse(t_parser *p);
#endif
