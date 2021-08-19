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
	printf("[ARGS]: \n");
	if (cmd->argv->items != NULL)
	{
		while (cmd->argv->items[++i])
			printf("%s - ", cmd->argv->items[i]);
	}
	printf("\n");
	/*if (io_mod)	
	{
		printf("IO_MODIFIER\n");
		i = -1;
		printf("OUTFILES\n");
		while (io_mod->out->items && io_mod->out->items[++i])
			printf("%s \n", io_mod->out->items[i]);
		i = -1;
		printf("INFILES\n");
		while (io_mod->in->items && io_mod->in->items[++i])
			printf("%s \n", io_mod->in->items[i]);
	}*/
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
		{
			print_ast_body(temp);
		}
		temp = temp->next;
	}
}
