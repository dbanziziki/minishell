#ifndef AST_H
# define AST_H

typedef struct s_AST
{
	enum
	{
		PROGRAM,
		CMD_AND_ARG,
		PIPE_CMD_AND_ARG,
	}				type;
	void			*body;
	struct s_AST	*next;
}					t_AST;

typedef struct	s_program
{
	int			nb_pipes;
	int			has_pipes;
}				t_program;

t_AST	*init_AST(int type, void *body);
void	addback_AST(t_AST **ast, t_AST *new);

#endif
