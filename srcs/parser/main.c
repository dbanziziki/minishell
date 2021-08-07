#include "parser.h"
#include <stdio.h>

void	free_all(t_parser *p, t_AST *root)
{
	free(p->token->value);
	free(p->token);
	free(p->t);
	free(p);
	free(root);
}

int main(int argc, char const *argv[])
{
	t_parser	*p;
	t_AST		*root;

	p = init_parser("cat main.c >> < >| grep>|>>< include");
	root = parse(p);
	printf("%p\n", root);
	free_all(p, root);
	return 0;
}
