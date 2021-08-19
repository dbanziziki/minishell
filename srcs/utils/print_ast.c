#include "parser.h"

#define GREEN printf("\033[0;32m");
# define RESET printf("\033[0m");
#define PURPLE printf("\033[0;35m");

static void	print_ast_body(t_AST *ast)
{
	t_cmd		*cmd;
	t_io_mod	*io_mod;
	int			i;

	i = -1;
	cmd = (t_cmd *)ast->body;
	io_mod = NULL;
	if (cmd->io_mod)
		io_mod = cmd->io_mod;
	if (ast->type == CMD_AND_ARG)
		printf("[CMD_AND_ARGS]\n");
	else
		printf("[PIPE_CMD_AND_ARGS]\n");
	printf("[CMD]: %s\n", cmd->cmd);	
	printf("[ARGS]: \n");
	if (cmd->argv->items != NULL)
	{
		PURPLE
		while (cmd->argv->items[++i])
			printf("%s\n", cmd->argv->items[i]);
		RESET
	}
	if (io_mod)
	{
		GREEN
		printf("[IO_MODIFIER]\n");
		RESET
		i = -1;
		printf("\t[OUTFILES]\n");
		PURPLE
		while (++i < io_mod->out->size)
			printf("\t%s \n", io_mod->out->items[i]);
		RESET
		i = -1;
		printf("\t[INFILES]\n");
		PURPLE
		while (++i < io_mod->in->size)
			printf("\t%s \n", io_mod->in->items[i]);
		RESET
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
		{
			print_ast_body(temp);
		}
		temp = temp->next;
	}
}
