#include <stdio.h>
#include "parser.h"

t_token	*eat(t_parser *p, int type)
{
	t_token	*token;

	token = p->token;
	if (!token)
	{
		print_error("minishell: unexpected end of input", NULL);
		p->flag = 1;
		return (NULL);
	}
	if (token->type != type)
	{
		print_error("minishell: parse error near ", token->value);
		p->flag = 1;
		return (NULL);
	}
	p->token = get_next_token(p->t);
	return (token);
}

static int	parsing_error(t_parser *p)
{
	print_error("minishell: unexpected token at ", p->token->value);
	p->flag = 1;
	return (-1);
}

static int	switch_token(t_parser *p, t_AST **ast)
{
	t_AST	*temp;

	if (p->token->type == WORD_TOKEN)
		parse_word(p, *ast);
	else if (p->token->type == PIPE_TOKEN)
	{
		temp = parse_pipe(p, *ast);
		if (!temp)
			return (-1);
		addback_AST(ast, temp);
	}
	else if (p->token->type == LESS_THAN_TOKEN
		|| p->token->type == GGREATER_THAN_TOKEN
		|| p->token->type == GREATER_THAN_TOKEN)
		parse_redirections(p, *ast);
	else if (p->token->type == DOUBLE_QUOTE_TOKEN)
		parse_double_quotes(p, *ast);
	else if (p->token->type == SIMPLE_QUOTE_TOKEN)
		parse_single_quotes(p, *ast);
	else if (p->token->type == DOLLARSIGN_TOKEN)
		parse_env_var(p, *ast);
	else if (p->token->type == HEREDOC_TOKEN)
		parse_heredoc(p, *ast);
	else
		return (parsing_error(p));
	return (1);
}

int	parse(t_parser *p, t_AST **ast)
{
	if (!p->token || p->token->type == EOF_TOKEN || p->flag)
		return (-1);
	if (switch_token(p, ast) == -1)
		return (-1);
	parse(p, ast);
	return (0);
}
