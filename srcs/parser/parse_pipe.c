#include "parser.h"

static void	update_prog(t_program **prog)
{
	if (!prog)
		return ;
	(*prog)->has_pipes = 1;
	(*prog)->nb_pipes++;
}

static t_cmd	*set_pipe_cmd(t_parser *p, t_AST *ast)
{
	t_cmd	*cmd;
	t_token	*token;

	if (p->token->type != WORD_TOKEN)
		return (init_cmd(NULL));
	token =	eat(p, WORD_TOKEN);
	if (!token)
		return (NULL);
	cmd = init_cmd(token->value);
	list_push(cmd->argv, token->value);
	free(token);
	eat_words(p, cmd);
	return (cmd);
}

t_AST	*parse_pipe(t_parser *p, t_AST *ast)
{
	t_token		*token;
	t_cmd		*cmd;
	t_program	*prog;
	t_AST		*last;

	last = get_last(&ast);
	token = eat(p, PIPE_TOKEN);
	if (!token)
		return (NULL);
	if (last->type == PROGRAM)
	{
		printf("minishell: parse error near `%s`\n", token->value);
		free(token->value);
		free(token);
		p->flag = 1;
		return (NULL);
	}
	prog = (t_program *)ast->body;
	update_prog(&prog);
	free(token->value);
	free(token);
	cmd = set_pipe_cmd(p, ast);
	return (init_AST(PIPE_CMD_AND_ARG, cmd));
}
