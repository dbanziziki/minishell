#include "parser.h"

void	parse_single_quotes(t_parser *p, t_AST *ast)
{
	t_token *token;
	t_cmd	*cmd;
	t_AST	*last;

	if (p->token->type != SIMPLE_QUOTE_TOKEN)
		return ;
	last = ast;
	while (last->next)
		last = last->next;
	cmd = NULL;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, SIMPLE_QUOTE_TOKEN);
	if (!token)
		return ;
	if (last->type == PROGRAM)
	{
		cmd = init_cmd(token->value);
		list_push(cmd->argv, token->value);
		addback_AST(&ast, init_AST(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)last->body;
		list_push(cmd->argv, token->value);
	}
	free(token);
	token = NULL;
	eat_words(p, cmd);
	parse_single_quotes(p, ast);
}