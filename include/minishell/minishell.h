#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "AST.h"
# include "parser.h"
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_sig
{
	int			sig_int;
	int			sig_quit;
	int			exit_status;
	pid_t		id;
}				t_sig;

extern t_sig	g_sig;

typedef struct s_minishell
{
	int			nb_proc;
	int			has_pipes;
	int			nb_pipe;
	int			**pipes;
	pid_t		*p_ids;
	t_parser	*p;
	t_AST		*ast;
	t_array		*var;
}				t_minishell;

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

int			cmd_and_args(t_minishell *ms, t_AST *curr_ast);
t_AST		*init_minishell_parse(t_minishell **ms, char *str);
t_minishell	*init_minishell_struct(char **env_v);
int			**init_pipes(int nb_pipes);
void		free_all(t_minishell *ms);
int			close_unused_pipes(int **pipes, int size, int i);
int			close_main_pipes(int **pipes, int size);
void		minishell(char **env_v);
int			find_cmd(t_array cmd, t_minishell *ms, t_AST *ast);
void		echo(char **s, t_AST *ast);
void		pwd(t_AST *ast);
void		change_dir(char *path, t_minishell *ms, t_AST *ast);
void		get_env(char **env_v, int flag, t_AST *ast);
void		unset(t_minishell *ms, char *var);
int			swap_lines(char **s1, char **s2);
void		for_dup(t_cmd *cmd);
void		action(int signum);
int			minishell_arg(char **envp, char *line);
void		time_to_exit(t_minishell *ms, char **line);
void		init_env(char **env_v, t_minishell *ms);
char		*get_env_v(char *key, t_array *var);
int			in_list(char *key, t_minishell *ms);
void		list_rm(t_array *list, void *to_rm, t_minishell *ms);
int			heredoc(t_minishell *ms, t_AST *curr_ast);
void		list_rm(t_array *list, void *to_rm, t_minishell *ms);
void		export_v(t_minishell *ms, char *new_arg, t_AST *ast);
void		exit_minishell(t_minishell *ms, int status);
int			redirect_output(t_cmd *cmd);
int			redirect_input(t_cmd *cmd);
int			pipe_stdout(t_minishell *ms, t_AST *curr_ast, t_cmd *cmd);
int			read_from_pipe(t_minishell *ms, t_cmd *cmd);
int			exec_cmd(t_cmd *cmd, t_array *var);
void		parse_line(t_minishell **ms, char *line);
char		*ms_readline(void);
int			execute(t_minishell *ms, char *line);
#endif
