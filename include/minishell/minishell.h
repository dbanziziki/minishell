#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "AST.h"
#include "parser.h"

typedef struct s_minishell
{
    int         **pipes;
    pid_t       *p_ids;
    t_parser    *p;
    t_AST       *ast;
}               t_minishell;

int cmd_and_args(t_AST *head, t_cmd *cmd);

#endif