#include "parser.h"

t_program	*init_prog()
{
	t_program	*prog;

	prog = (t_program *)malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	prog->has_pipes = 0;
	prog->nb_pipes = 0;
	return (prog);
}