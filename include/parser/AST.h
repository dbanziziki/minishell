#ifndef AST_H
# define AST_H

typedef struct s_AST
{
	enum
	{
		PROGRAM,
		CMD_AND_ARG,
		PIPE_CMD_AND_ARG,
		HEREDOC_AND_ARG,
	}				type;
	void			*body;
	struct s_AST	*next;
	struct s_AST	*prev;
}					t_AST;

typedef struct	s_program
{
	int			nb_pipes;
	int			has_pipes;
}				t_program;

t_AST		*init_AST(int type, void *body);
void		addback_AST(t_AST **ast, t_AST *new);
t_program	*init_prog();
void		print_ast(t_AST *ast);
#endif
