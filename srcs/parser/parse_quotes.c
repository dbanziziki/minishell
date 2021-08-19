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

int	get_var_start(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
			return (i + 1);
	}
	return (0);
}

int	get_token_len(char *line)
{
	int	token_len;
	int	i;

	i = -1;
	token_len = 0;
	while (line[++i] && line[i] != ' ')
		token_len++;
	return (token_len);
}

static char	*insert_var(char *join, char *var_val)
{
	char	*res;
	int		tot_len;
	int		var_start;
	int		var_len;
	int		token_len;

	var_start = get_var_start(join);
	token_len = get_token_len(join + var_start);
	var_len = ft_strlen(var_val);
	tot_len = var_start + var_len + (ft_strlen(join) - (token_len + var_start));
	res = (char *)malloc(sizeof(char) * tot_len);
	if (!res)
		return (NULL);
	ft_memcpy(res, join, var_start - 1);
	ft_memcpy(res + (var_start - 1), var_val, var_len);
	ft_memcpy(res + ((var_start - 1) + var_len),
		join + ((var_start) + token_len),
		ft_strlen(join + ((var_start) + token_len)));
	res[tot_len - 1] = 0;
	free(join);
	return (res);
}

static char	*parse_str(char *str)
{
	char	*res;
	char	*env_var;

	if (!ft_strchr(str, '$'))
		return (str);
	res = ft_strdup(str);
	while (*str)
	{
		if (*str == '$')
		{
			env_var = get_env_var(str + 1);
			res = insert_var(res, env_var);
		}
		str++;
	}
	return (res);
}

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
	parsed = parse_str(token->value);
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
	while (p->token->type == WORD_TOKEN)
	{
		token = eat(p, WORD_TOKEN);
		list_push(cmd->argv, token->value);
		free(token);
		token = NULL;
	}
	parse_double_quotes(p, ast);
}
