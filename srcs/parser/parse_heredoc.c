#include "parser.h"

void	addback_hd(t_heredoc **hd, t_heredoc *new)
{
	t_heredoc	*temp;

	if (!hd)
		return ;
	if (!(*hd))
	{
		*hd = new;
		return ;
	}
	temp = *hd;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_heredoc	*init_heredoc(char *delimiter)
{
	t_heredoc	*hd;

	hd = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!hd)
		return (NULL);
	hd->delimiter = delimiter;
	hd->next = NULL;
	return (hd);
}

void	set_heredoc(t_parser *p, t_AST *ast, t_heredoc	**hd)
{
	t_token		*token;

	hd = NULL;
	token = eat(p, HEREDOC_TOKEN);
	free(token->value);
	free(token);
	token = eat(p, WORD_TOKEN);
	addback_hd(hd, init_heredoc(token->value));
	free(token);
}

void	set_cmd_and_arg(t_parser *p, t_AST **ast, t_heredoc *hd)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	if (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		cmd = init_cmd(token->value);
		list_push(cmd->argv, token->value);
		free(token);
		eat_words(p, cmd);
		cmd->hd = hd;
	}
	else
	{
		cmd = init_cmd(NULL);
		cmd->hd = hd;
	}
	addback_AST(ast, init_AST(CMD_AND_ARG, cmd));
}

void	parse_heredoc(t_parser *p, t_AST *ast)
{
	t_token		*token;
	t_heredoc	*hd;
	t_AST		*last;
	t_cmd		*cmd;

	if (p->token->type != HEREDOC_TOKEN)
		return ;
	last = ast;
	hd = NULL;
	cmd = NULL;
	while (last->next)
		last = last->next;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, HEREDOC_TOKEN);
	free(token->value);
	free(token);
	token = eat(p, WORD_TOKEN);
	if (cmd && cmd->hd)
		addback_hd(&(cmd->hd), init_heredoc(token->value));
	else
		addback_hd(&hd, init_heredoc(token->value));
	free(token);
	if (cmd == NULL)
		set_cmd_and_arg(p, &last, hd);
	/*else
	{
		if (!cmd->cmd)
		{
			token = eat(p, WORD_TOKEN);
			cmd->cmd = token->value;
			list_push(cmd->argv, token->value);
			free(token);
		}
		eat_words(p, cmd);
	}*/
}