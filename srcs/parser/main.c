#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

/*void	free_all(t_parser *p, t_AST *root)
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
}*/

int main(int argc, char const *argv[])
{
	t_parser	*p;
	t_AST		*root;
	t_cmd		*cmd;
	int			i;
	t_program	*prog;
	t_io_mod	*io_mod;
	char		*line;

	prog = (t_program *)malloc(sizeof(t_program));
	prog->has_pipes = 0;
	prog->nb_pipes = 0;
	root = init_AST(PROGRAM, prog);
	#ifdef __APPLE__
	line = readline("(TEST)> ");
	#else
	get_next_line(STDIN_FILENO, &line);
	#endif
	p = init_parser(line);
	//p = init_parser("cat test.c | grep include > outfile");
	i = -1;
	parse(p, &root);
	print_ast(root);
	return 0;
}
