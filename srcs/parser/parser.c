#include <stdio.h>
#include "parser.h"

t_parser	*init_parser(char *str)
{
	t_tokenizer	*t;
	t_parser	*p;

	t = init_tokenizer(str);
	if (!t)
		return (NULL);
	p = (t_parser *)malloc(sizeof(t_parser));
	if (!t)
		return (NULL);
	p->t = t;
	p->flag = 0;
	p->token = get_next_token(t);
	return (p);
}

t_token	*eat(t_parser *p, int type)
{
	t_token	*token;

	token = p->token;
	if (!token)
	{
		printf("minishell: unexpected end of input\n");
		p->flag = 1;
		return (NULL);
	}
	if (token->type != type)
	{
		printf("minishell: parse error near `%s`\n", token->value);
		p->flag = 1;
		return (NULL);
	}
	p->token = get_next_token(p->t);
	return (token);
}

t_AST	*parse_pipe(t_parser *p, t_AST *ast)
{
	t_token		*token;
	t_cmd		*cmd;
	t_program	*prog;
	t_AST		*last;

	last = ast;
	while (last->next)
		last = last->next;
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
	prog->has_pipes = 1;
	prog->nb_pipes++;
	free(token->value);
	free(token);
	token =	eat(p, WORD_TOKEN);
	if (!token)
		return (NULL);
	cmd = init_cmd(token->value);
	list_push(cmd->argv, token->value);
	free(token);
	eat_words(p, cmd);
	return (init_AST(PIPE_CMD_AND_ARG, cmd));
}

void	parse_env_var(t_parser *p, t_AST *ast)
{
	t_token		*token;
	t_cmd		*cmd;
	char		*env_var;

	token = eat(p, DOLLARSIGN_TOKEN);
	if (!token)
		return ;
	env_var = getenv(++(token->value));
	while (ast->next)
		ast = ast->next;
	if (ast->type == PROGRAM)
	{
		cmd = init_cmd(env_var);
		list_push(cmd->argv, env_var);
		addback_AST(&ast, init_AST(CMD_AND_ARG, cmd));
	}
	else
	{
		cmd = (t_cmd *)ast->body;
		list_push(cmd->argv, env_var);
	}
	free(token);
}

int	parse(t_parser *p, t_AST **ast)
{
	int flag;
	t_AST	*temp;

	flag = 1;
	temp = NULL;
	if (!p->token || p->token->type == EOF_TOKEN || p->flag)
		return (flag);
	if (p->token->type == WORD_TOKEN)
		parse_word(p, *ast);
	else if(p->token->type == PIPE_TOKEN)
	{
		temp = parse_pipe(p, *ast);
		if (!temp)
			return (1);
		addback_AST(ast, temp);
	}
	else if (p->token->type == LESS_THAN_TOKEN ||
		p->token->type == GGREATER_THAN_TOKEN ||
		p->token->type == GREATER_THAN_TOKEN)
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
	{
		printf("unexpected token at `%s`\n", p->token->value);
		p->flag = 1;
		return (flag);
	}
	parse(p, ast);
	return (flag);
}
