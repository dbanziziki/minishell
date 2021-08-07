#include "parser.h"

t_AST	*init_AST(int type)
{
	t_AST *AST;

	AST = malloc(sizeof(t_AST));
	if (!AST)
		return (NULL);
	AST->type = type;
	return (AST);
}


