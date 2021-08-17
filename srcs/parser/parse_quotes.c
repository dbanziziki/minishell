#include "parser.h"

static char	*get_env_var(char *str)
{
	char	*env_var;
	int		var_len;
	char	*temp;

	var_len = -1;
	while (str[++var_len] && str[var_len] != ' ');
	temp = ft_strndup(str, var_len);
	env_var = getenv(temp);
	free(temp);
	return (env_var);
}

static char	*insert_var(char *str, char *env_var, int n)
{
	char	*res;
	size_t	tot_len;
	size_t	var_start;
	size_t	var_len;

	var_start = -1;
	while (str[++var_start] && str[var_start] != '$');
	var_start++;
	var_len = ft_strlen(env_var);
	tot_len = var_start + var_len + (ft_strlen(str) - (n + var_start));
	res = (char *)malloc(sizeof(char) * (tot_len + 1));
	if (!res)
		return (NULL);
	printf("%ld\n", var_start);
	ft_memcpy(res, str, var_start - 1);
	ft_memcpy(res + (var_start - 1), env_var, var_len);
	ft_memcpy(res + ((var_start - 1) + var_len),
		str + ((var_start) + n),
		ft_strlen(str + ((var_start) + n)));
	res[tot_len] = 0;
	printf("res is: %s\n", res);
	return (res);
}

static char	*parse_str(char *str)
{
	char	*res;
	char	*env_var;
	int		n;

	if (!ft_strchr(str, '$'))
		return (str);
	n = 0;
	res = ft_strdup(str);
	while (*str)
	{
		if (*str == '$')
		{
			while (str[++n] && str[n] != ' ');
			env_var = get_env_var(str + 1);
			res = insert_var(res, env_var, n);
		}
		str++;
		n = 0;
	}
	return (res);
}

void	parse_double_quotes(t_parser *p, t_AST *ast)
{
	t_token	*token;
	t_cmd	*cmd;
	t_AST	*last;

	last = ast;
	while (last->next)
		last = last->next;
	cmd = NULL;
	if (last->type != PROGRAM)
		cmd = (t_cmd *)last->body;
	token = eat(p, DOUBLE_QUOTE_TOKEN);
	/* check if we have some env var to interpret in token->value */
	parse_str(token->value);
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
}
