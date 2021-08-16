#include "parser.h"
#include <stdio.h>

void	free_all(t_parser *p, t_AST *root)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)root->next->body;
	if (cmd->io_mod)
	{
		if (cmd->io_mod->infile)
			free(cmd->io_mod->infile);
		if (cmd->io_mod->outfile)
			free(cmd->io_mod->outfile);
		free(cmd->io_mod);
	}
	free(cmd);
	free(root->next);
	free(p->token->value);
	free(p->token);
	free(p->t);
	free(p);
	free(root->body);
	free(root);
}

int main(int argc, char const *argv[])
{
	t_parser	*p;
	t_AST		*root;
	t_cmd		*cmd;
	int			i;
	t_program	*prog;
	t_io_mod	*io_mod;

	prog = (t_program *)malloc(sizeof(t_program));
	prog->has_pipes = 0;
	prog->nb_pipes = 0;
	root = init_AST(PROGRAM, prog);
	p = init_parser("> infile");
	//p = init_parser("cat test.c | grep include > outfile");
	i = -1;
	root = parse(p, root);
	if (!prog->has_pipes)
		printf("NOP\n");
	print_ast(root);
	/*if (root->type == PROGRAM)
		printf("OK\n");
	cmd = (t_cmd *)(root->next->body);
	io_mod = cmd->io_mod;
	if (io_mod)
		printf("%s\n", io_mod->infile);
	printf("[cmd]: %s [args] ->", cmd->cmd);
	printf("[");
	if (io_mod)
	while (cmd->argv->items[++i])
		printf("%s, ", (char *)(cmd->argv->items[i]));
	printf("]\n");
	i = -1;
	while (++i < cmd->argv->size)
		free(cmd->argv->items[i]);
	free(cmd->argv->items);
	free(cmd->argv);
	free_all(p, root);*/
	return 0;
}
