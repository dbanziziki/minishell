#include "parser.h"

static void	set_cmd_and_arg(t_parser *p, t_AST **ast, t_list *hd)
{
	t_cmd	*cmd;
	t_token	*token;

	cmd = NULL;
	if (p->token->e_type == WORD_TOKEN)
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
	if (cmd->io_mod)
		cmd->io_mod->hd_flag = 1;
	addback_AST(ast, init_AST(CMD_AND_ARG, cmd));
}

static void	set_heredoc(t_parser *p, t_AST *last, t_cmd *cmd)
{
	t_token	*token;
	t_list	*hd;

	hd = NULL;
	token = eat(p, WORD_TOKEN);
	if (!token)
		return ;
	if (cmd && cmd->hd)
		ft_lstadd_back(&(cmd->hd), ft_lstnew(token->value));
	else
		ft_lstadd_back(&hd, ft_lstnew(token->value));
	free(token);
	if (cmd == NULL)
		set_cmd_and_arg(p, &last, hd);
	else
	{
		if (cmd->io_mod)
			cmd->io_mod->hd_flag = 1;
		ft_lstadd_back(&(cmd->hd), hd);
	}
}

void	parse_heredoc(t_parser *p, t_AST *ast)
{
	t_token		*token;
	t_list		*hd;
	t_AST		*last;
	t_cmd		*cmd;

	if (p->token->e_type != HEREDOC_TOKEN)
		return ;
	last = get_last(&ast);
	hd = NULL;
	cmd = NULL;
	if (last->e_type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, HEREDOC_TOKEN);
	if (!token)
		return ;
	free(token->value);
	free(token);
	set_heredoc(p, last, cmd);
}
