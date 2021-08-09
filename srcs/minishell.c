#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "parser.h"
#include "AST.h"

void	free_all(t_parser *p, t_AST *root)
{
	int		i;
	t_cmd	*cmd;

	cmd = (t_cmd *)root->next->body;
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
    char        *line;
    t_AST       *ast;
    t_parser    *p;
    t_cmd       *cmd;
    int         i;
    pid_t       pid;
    char        *cmd_path;

    while (1)
    {
        i = -1;
        line = readline("> ");
        p = init_parser(line);
        ast = init_AST(PROGRAM, NULL);
        ast = parse(p, ast);
        cmd = (t_cmd *)ast->next->body;
        //while (cmd->argv->items[++i])
          //  printf("%s ", (char *)(cmd->argv->items[i]));
        pid = fork();
        if (pid == 0)
        {
            //cmd_path = ft_strjoin_sep("/bin", cmd->cmd, '/');
            execvp(cmd->cmd, (char **)(cmd->argv->items));
            printf("%s not found\n", cmd->cmd);
            return (1);
        }
        printf("\n");
        free(line);
        free_all(p, ast);
    }
    return 0;
}
