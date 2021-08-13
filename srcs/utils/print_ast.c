#include "parser.h"

static void	print_ast_body(t_AST *ast)
{
	t_cmd		*cmd;
	t_io_mod	*io_mod;
	int			i;

	i = -1;
	cmd = (t_cmd *)ast->body;
	if (cmd->io_mod)
		io_mod = cmd->io_mod;
	if (ast->type == CMD_AND_ARG)
		printf("CMD_AND_ARGS\n");
	else
		printf("PIPE_CMD_AND_ARGS\n");
	printf("[CMD]: %s\n", cmd->cmd);	
	printf("[ARGS]: ");
	while (cmd->argv->items[++i])
		printf("%s ", cmd->argv->items[i]);
	printf("\n");
	if (io_mod)	
	{
		printf("IO_MODIFIER\n");
		printf("[INFILE]: %s \n", io_mod->infile);
		printf("[OUTFILE]: %s \n", io_mod->outfile);
	}
}

void	print_ast(t_AST *ast)
{
	t_AST		*temp;

	if (!ast)
		return;	
	temp = ast->next;
	while (temp)
	{
		if (temp->body)
			print_ast_body(temp);
		temp = temp->next;
	}
}
