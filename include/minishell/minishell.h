#ifndef MINISHELL_H
# define MINISHELL_H

#ifdef __APPLE__
#include <readline/readline.h>
#include <readline/history.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "AST.h"
#include "parser.h"
#include "libft.h"

# define RESET "\033[0m"
# define RED "\033[1;31m"

typedef struct s_minishell
{
    int         nb_proc;
    int         **pipes;
    pid_t       *p_ids;
    t_parser    *p;
    t_AST       *ast;
}               t_minishell;

int         cmd_and_args(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd);
t_AST	    *init_minishell_parse(t_minishell **ms, char *str);
t_minishell *init_minishell_struct(void);
int         **init_pipes(int nb_pipes);
void        free_all(t_parser *p, t_AST *root);
int         close_unused_pipes(int **pipes, int size, int i);
int         close_main_pipes(int **pipes, int size, int i);
#endif