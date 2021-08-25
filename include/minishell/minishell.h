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
	int			exit_status;
	int			has_pipes;
	int			nb_pipe;
    int         **pipes;
    pid_t       *p_ids;
    t_parser    *p;
    t_AST       *ast;
	t_array		*var;
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

int         cmd_and_args(t_minishell *ms, t_AST *curr_ast);
t_AST	    *init_minishell_parse(t_minishell **ms, char *str);
t_minishell *init_minishell_struct(char **env_v);
int         **init_pipes(int nb_pipes);
void        free_all(t_minishell *ms);
int         close_unused_pipes(int **pipes, int size, int i);
void        hook(void);
int         close_main_pipes(int **pipes, int size);
void        minishell(char **env_v);
int			find_cmd(t_array cmd, t_minishell *ms);
void		echo(char **s);
void		pwd(void);
void		change_dir(char *path);
void		time_to_exit(t_minishell *ms);
int 		main(int argc, char const *argv[], char **envp);
void		init_env(char **env_v, t_minishell *ms);
char 		*get_env_v(char *key, t_array *var);
int			in_list(char *key, t_minishell *ms);
void    	list_rm(t_array *list, void *to_rm, t_minishell *ms);
int			heredoc(t_minishell *ms, t_AST *curr_ast);
#endif