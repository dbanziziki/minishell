#ifndef PARSER_H
# define PARSER_H

#include "tokenizer.h"

typedef struct s_parser
{
    t_tokenizer *t;
    t_token     *lookahead;
}               t_parser;

typedef struct s_AST_body
{
    char                *type;
    char                *value;
    struct s_AST_body   *next;
}               t_body;

typedef struct s_AST
{
    t_type      type;
    void        *body;
    t_parser    *parser;
}               t_AST;


#endif