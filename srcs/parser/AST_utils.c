#include "parser.h"

t_program	*init_prog(void)
{
	t_program	*prog;

	prog = (t_program *)malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	prog->has_pipes = 0;
	prog->nb_pipes = 0;
	return (prog);
}

t_AST	*get_last(t_AST **ast)
{
	t_AST	*temp;

	temp = *ast;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
