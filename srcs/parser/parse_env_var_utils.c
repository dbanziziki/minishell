#include "parser.h"

static char	*get_env_var(char *str, t_array *var)
{
	char	*env_var;
	int		var_len;
	char	*temp;

	var_len = -1;
	while (str[++var_len] && str[var_len] != ' ')
		;
	temp = ft_strndup(str, var_len);
	env_var = get_env_v(temp, var);
	free(temp);
	return (env_var);
}

static int	get_var_start(char *line)
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

static int	get_token_len(char *line)
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

char	*parse_str(char *str, t_array *var)
{
	char	*res;
	char	*env_var;
	char	*temp;

	temp = str;
	if (!ft_strchr(temp, '$'))
		return (str);
	res = ft_strdup(str);
	temp = str;
	while (*temp)
	{
		if (*temp == '$')
		{
			env_var = get_env_var(temp + 1, var);
			res = insert_var(res, env_var);
		}
		temp++;
	}
	return (res);
}
