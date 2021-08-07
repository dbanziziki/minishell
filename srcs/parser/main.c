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

	p = init_parser("cat hello main.c hello hello >> < >| grep>|>>< include");
	i = -1;
	root = parse(p);
	cmd = (t_cmd *)(root->next->body);
	printf("%d\n", ((t_program *)root->body)->nb_pipes);
	if (root->next)
		printf("%s\n", cmd->cmd);
	while (++i < cmd->argv->size)
		printf("%s\n", (char *)(cmd->argv->items[i]));
	i = -1;
	while (++i< cmd->argv->size)
		free(cmd->argv->items[i]);	
	free(cmd->argv->items);
	free(cmd->argv);
	free(cmd->cmd);
	free_all(p, root);
	return 0;
}
