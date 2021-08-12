#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "AST.h"
# include "parser.h"
# include "libft.h"
# ifdef __APPLE__
#  include <readline/readline.h>
#  include <readline/history.h>
# endif

typedef struct s_minishell
{
    int         **pipes;
    pid_t       *p_ids;
    t_parser    *p;
    t_AST       *ast;
}               t_minishell;

int         cmd_and_args(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd);
t_AST	    *init_minishell_parse(t_minishell **ms, char *str);
t_minishell *init_minishell_struct(void);
int         **init_pipes(int nb_proc);
void        free_all(t_parser *p, t_AST *root);
int         close_unused_pipes(int **pipes, int size, int i);
void        hook(void);

#endif