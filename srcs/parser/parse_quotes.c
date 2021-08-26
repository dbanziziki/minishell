#include "parser.h"

void	parse_double_quotes(t_parser *p, t_AST *ast)
{
	t_token	*token;
	t_cmd	*cmd;
	t_AST	*last;
	char	*parsed;

	if (p->token->type != DOUBLE_QUOTE_TOKEN)
		return ;
	last = ast;
	while (last->next)
		last = last->next;
	cmd = NULL;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, DOUBLE_QUOTE_TOKEN);
	if (!token)
		return ;
	parsed = parse_str(token->value, p->var);
	/* check if we have some env var to interpret in token->value */
	if (last->type == PROGRAM)
	{
		cmd = init_cmd(parsed);
		list_push(cmd->argv, parsed);
		addback_AST(&ast, init_AST(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)last->body;
		list_push(cmd->argv, parsed);
	}
	free(token);
	token = NULL;
	eat_words(p, cmd);
	parse_double_quotes(p, ast);
}
