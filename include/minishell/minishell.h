#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "AST.h"
#include "parser.h"
#include "libft.h"
#ifdef __APPLE__
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define RESET "\033[0m"
#define RED "\033[1;31m"

typedef struct s_minishell
{
    int         nb_proc;
	int			has_pipes;
    int         **pipes;
    pid_t       *p_ids;
    t_parser    *p;
    t_AST       *ast;
	char		**env_v;
}               t_minishell;

typedef struct s_buildin
{
	enum
	{
		ECHO_F,
		PWD_F,
		CD_F,
		EXIT_F,
		EXPORT_F,
		UNSET_F,
		ENV_F
	}			e_build;
}				t_buildin;

int         cmd_and_args(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd);
t_AST	    *init_minishell_parse(t_minishell **ms, char *str);
t_minishell *init_minishell_struct(void);
int         **init_pipes(int nb_pipes);
void        free_all(t_minishell *ms);
int         close_unused_pipes(int **pipes, int size, int i);
void        hook(void);
int         close_main_pipes(int **pipes, int size);
void        minishell(char **env_v);
int			find_cmd(t_array cmd, t_array flags, char **env_v);
void		echo(char *s, char *flag);
void		pwd(void);
void		change_dir(char *path);
void		time_to_exit(void);

#endif