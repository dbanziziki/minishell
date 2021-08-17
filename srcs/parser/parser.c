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
		exit(EXIT_FAILURE);
		return (NULL);
	}
	if (token->type != type)
	{
		printf("minishell: parse error near `%s`\n", token->value);
		exit(EXIT_FAILURE);
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

	token = eat(p, PIPE_TOKEN);
	prog = (t_program *)ast->body;
	prog->has_pipes = 1;
	prog->nb_pipes++;
	free(token->value);
	free(token);
	token =	eat(p, WORD_TOKEN);
	cmd = init_cmd(token->value);
	list_push(cmd->argv, token->value);
	free(token);
	while (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		list_push(cmd->argv, token->value);
		free(token);
		token =	NULL;
	}
	return (init_AST(PIPE_CMD_AND_ARG, cmd));
}

void	parse_env_var(t_parser *p, t_AST *ast)
{
	t_token		*token;
	t_cmd		*cmd;
	char		*env_var;

	token = eat(p, DOLLARSIGN_TOKEN);
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
}

t_AST	*parse(t_parser *p, t_AST *ast)
{
	if (!p->token || p->token->type == EOF_TOKEN)
		return (ast);
	if (p->token->type == WORD_TOKEN)
		addback_AST(&ast, parse_word(p));
	else if(p->token->type == PIPE_TOKEN)
		addback_AST(&ast, parse_pipe(p, ast));
	else if (p->token->type == REDIRECT_OUTPUT ||
		p->token->type == REDIRECT_INPUT ||
		p->token->type == REDIRECT_OUTPUT_APPEND)
		parse_redirection(p, ast);
	else if (p->token->type == DOUBLE_QUOTE_TOKEN)
		parse_double_quotes(p, ast);
	else if (p->token->type == DOLLARSIGN_TOKEN)
		parse_env_var(p, ast);
	else
	{
		printf("unexpected token at `%s`\n", p->token->value);
		exit(1);
	}
	parse(p, ast);
	return (ast);
}

