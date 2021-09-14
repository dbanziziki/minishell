#include "minishell.h"

t_sig	g_sig;

static void	set_cmd(t_AST *ast, char *env_var)
{
	t_cmd	*cmd;

	cmd = NULL;
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

void	parse_env_var(t_parser *p, t_AST *ast)
{
	t_token		*token;
	char		*env_var;

	token = eat(p, DOLLARSIGN_TOKEN);
	if (!token)
		return ;
	if (!ft_strcmp(token->value, "$?"))
		env_var = ft_itoa(g_sig.exit_status);
	else
		env_var = ft_strdup(get_env_v((token->value) + 1, p->var));
	while (ast->next)
		ast = ast->next;
	set_cmd(ast, env_var);
	free(token->value);
	free(token);
}
