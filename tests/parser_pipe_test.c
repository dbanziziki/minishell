#include "parser.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	t_parser	*p;
	t_AST		*root;
	t_cmd		*cmd;
	t_cmd		*cmd2;
	int			i;
	t_program	*base;
	t_io_mod	*io_mod;

	base = (t_program *)malloc(sizeof(t_program));
	base->has_pipes = 0;
	base->nb_pipes = 0;
	root = init_AST(PROGRAM, base);
	p = init_parser("cat main.c | grep include");
	i = -1;
	root = parse(p, root);
	cmd = (t_cmd *)(root->next->body);
	cmd2 = (t_cmd *)(root->next->next->body);
    while (cmd->argv->items[++i])
		printf("%s, ", (char *)(cmd->argv->items[i]));
	io_mod = cmd->io_mod; 
    return 0;
}
