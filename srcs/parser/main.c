#include "parser.h"
#include <stdio.h>

void	free_all(t_parser *p, t_AST *root)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)root->next->body;
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
	t_program	*base;

	base = (t_program *)malloc(sizeof(t_program));
	base->has_pipes = 0;
	base->nb_pipes = 0;
	root = init_AST(PROGRAM, base);
	p = init_parser("& cat hello main.c");
	i = -1;
	root = parse(p, root);
	cmd = (t_cmd *)(root->next->body);
	printf("[cmd]: %s [args] ->", cmd->cmd);
	printf("[");
	while (cmd->argv->items[++i])
		printf("%s, ", (char *)(cmd->argv->items[i]));
	printf("]\n");
	i = -1;
	while (++i< cmd->argv->size)
		free(cmd->argv->items[i]);	
	free(cmd->argv->items);
	free(cmd->argv);
	free_all(p, root);
	return 0;
}
