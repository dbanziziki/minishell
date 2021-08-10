#include "minishell.h"
#include <stdio.h>

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

t_program	*init_prog()
{
	t_program	*prog;

	prog = (t_program *)malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	prog->nb_pipes = 0;
	prog->nb_pipes = 0;
	return (prog);
}

t_minishell	*init_minishell_struct()
{
	t_minishell	*ms;

	ms = (t_minishell *)malloc(sizeof(t_minishell));
	if (!ms)
		return (NULL);
	ms->ast = 0;
	ms->p = 0;
	ms->pipes = 0;
	return (ms);
}

t_AST	*init_minishell_parse(t_minishell **ms, char *str)
{
	t_AST		*ast;
	t_program	*prog;
	t_parser	*p;

	p = init_parser(str);
	prog = init_prog();
	if (!prog || !p)
		return (NULL);
	ast = init_AST(PROGRAM, prog);
	ast = parse(p, ast);
	if (!ast)
		return (NULL);
	(*ms)->ast = ast;
	(*ms)->p = p;
	return (ast);
}

int main(int argc, char const *argv[])
{
	t_minishell	*ms;
	char		*line;
	t_cmd		*cmd;
	//t_cmd		*cmd1;
	int			i;
	pid_t		pid;
	t_program	*prog;

	ms = init_minishell_struct();
	if (!ms)
		return (1);
	while (1)
	{
		i = -1;
		line = readline("(minishell)> ");
		ms->ast = init_minishell_parse(&ms, line);
		prog = (t_program *)ms->ast->body;
		cmd = (t_cmd *)ms->ast->next->body;
		/*if (ms->ast->next->next)
		{
			cmd1 = (t_cmd *)ms->ast->next->next->body;
			if (ms->ast->body && prog->has_pipes)
				printf("this prog has %d pipes\n", prog->nb_pipes);
		}*/
		//while (cmd->argv->items[++i])
		//  printf("%s ", (char *)(cmd->argv->items[i]));
		//printf("[INFILE]: %s\n", cmd->io_mod->infile);
		pid = fork();
		if (pid == 0)
		{
			cmd_and_args(ms->ast, cmd);
			return (1);
		}
		wait(NULL);
		printf("\n");
		free(line);
		free_all(ms->p, ms->ast);
	}
	return 0;
}
