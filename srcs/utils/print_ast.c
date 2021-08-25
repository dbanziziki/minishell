#include "parser.h"

#define GREEN printf("\033[0;32m");
# define RESET printf("\033[0m");
#define PURPLE printf("\033[0;35m");
#define YELLOW printf("\e[0;33m");
#define BLUE printf("\e[0;34m");
#define RED printf("\e[0;31m");

static void	print_ast_body(t_AST *ast)
{
	t_cmd		*cmd;
	t_io_mod	*io_mod;
	int			i;
	t_heredoc	*hd;

	i = -1;
	cmd = (t_cmd *)ast->body;
	io_mod = NULL;
	hd = NULL;
	if (cmd->io_mod)
		io_mod = cmd->io_mod;
	if (cmd->hd)
		hd = cmd->hd;
	if (hd)	
	{
		while (hd)
		{
			printf("delimiter: %s\n", hd->delimiter);
			hd = hd->next;
		}
	}
	if (ast->type == CMD_AND_ARG)
	{
		YELLOW
		printf("[CMD_AND_ARGS]\n");
		RESET
	}
	else
	{
		BLUE
		printf("[PIPE_CMD_AND_ARGS]\n");
		RESET
	}
	GREEN
	printf("[CMD]: %s\n", cmd->cmd);	
	RESET
	printf("[ARGS]: ");
	i = 0;
	if (cmd->argv->items != NULL)
	{
		PURPLE
		while (cmd->argv->items[++i])
			printf("%s ", cmd->argv->items[i]);
		RESET
	}
	printf("\n");
	if (io_mod)
	{
		GREEN
		printf("[IO_MODIFIER]\n");
		RESET
		i = -1;
		RED
		printf("\t[OUTFILES]\n");
		RESET
		PURPLE
		while (++i < io_mod->out->size)
			printf("\t%s \n", io_mod->out->items[i]);
		RESET
		i = -1;
		RED
		printf("\t[INFILE]\n");
		RESET
		PURPLE
		if (io_mod->infile)
			printf("\t%s \n", io_mod->infile);
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
			print_ast_body(temp);
		temp = temp->next;
	}
}
