#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "AST.h"
#include <fcntl.h>
#include <sys/wait.h>

void free_all(t_parser *p, t_AST *root)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)root->next->body;
	if (cmd->io_mod)
	{
		if (cmd->io_mod->infile)
			free(cmd->io_mod->infile);
		if (cmd->io_mod->oufile)
			free(cmd->io_mod->oufile);
		free(cmd->io_mod);
	}
	while (++i < cmd->argv->size)
		free(cmd->argv->items[i]);
	free(cmd->argv->items);
	free(cmd->argv);
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
	char		*line;
	t_AST		*ast;
	t_parser	*p;
	t_cmd		*cmd;
	int			i;
	pid_t		pid;
	char		*cmd_path;
	int			fd;

	while (1)
	{
		i = -1;
		line = readline("(minishell)> ");
		p = init_parser(line);
		ast = init_AST(PROGRAM, NULL);
		ast = parse(p, ast);
		cmd = (t_cmd *)ast->next->body;
		//while (cmd->argv->items[++i])
		//  printf("%s ", (char *)(cmd->argv->items[i]));
		//printf("[INFILE]: %s\n", cmd->io_mod->infile);
		pid = fork();
		if (pid == 0)
		{
			//cmd_path = ft_strjoin_sep("/bin", cmd->cmd, '/');
			if (cmd->io_mod && cmd->io_mod->type == REDIRECT_OUTPUT)
			{
				fd = open(cmd->io_mod->oufile, O_TRUNC | O_CREAT | O_WRONLY, 0777);
				if (fd < 0)
					return (1);
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
			else if (cmd->io_mod && cmd->io_mod->type == REDIRECT_INPUT)
			{
				fd = open(cmd->io_mod->infile, O_RDONLY);
				if (fd < 0)
					return (1);
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			execvp(cmd->cmd, (char **)(cmd->argv->items));
			printf("%s not found\n", cmd->cmd);
			return (1);
		}
		wait(NULL);
		printf("\n");
		free(line);
		free_all(p, ast);
	}
	return 0;
}
