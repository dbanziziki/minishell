#ifndef AST_H
# define AST_H

typedef struct s_AST
{
	enum
	{
		PROGRAM,
		CMD_AND_ARG,
	} type;
}               t_AST;

t_AST	*init_AST(int type);

#endif
