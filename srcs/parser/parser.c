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
	free(token);
	while (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		printf("[PIPE CMD_AND_ARG]: [%s]\n", token->value);
		list_push(cmd->argv, token->value);
		free(token);
		token =	NULL;
	}
	/* parse redirections if any*/
	return (init_AST(PIPE_CMD_AND_ARG, cmd));
}

t_AST	*parse(t_parser *p, t_AST *ast)
{
	if (p->token->type == EOF_TOKEN)
		return (ast);
	if (p->token->type == WORD_TOKEN)
		addback_AST(&ast, parse_word(p));
	else if(p->token->type == PIPE_TOKEN)
		addback_AST(&ast, parse_pipe(p, ast));
	else
	{
		printf("here\n");
		printf("unexpected token at `%s`\n", p->token->value);
		exit(1);
	}
	/*add a token to parse in an if statement*/
	parse(p, ast);
	return (ast);
}

