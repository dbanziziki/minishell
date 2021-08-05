#include <stdlib.h>
#include <stdio.h>

typedef enum e_states t_states;

enum e_states
{
	WORD,
	REDIRECT,
	UNKNOWN,
	HEREDOC,
	WHITE_SPACE = ' ',
	PIPE = '|',
};

typedef struct s_token
{
	t_states				type;
	char				*value;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (*((char *)s1 + i)
		&& *((char *)s1 + i) == *((char *)s2 + i) && i < n - 1)
		i++;
	if (n)
		return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
	return (0);
}

int		ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int		ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr_dest;
	unsigned char	*ptr_src;

	ptr_dest = dest;
	ptr_src = (unsigned char *)src;
	i = -1;
	if (!dest && !src)
		return (NULL);
	while (++i < n)
		*(ptr_dest + i) = *(ptr_src + i);
	return (dest);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;

	if (!s)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ft_memcpy(res, s, n);
	res[n] = '\0';
	return (res);
}

t_token	*new_token(t_states type, char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->type = type;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_back(t_token **head, t_token *new)
{
	t_token *temp;

	if (!head)
		return ;
	if (!(*head)) 
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

int	parser(t_token *tokens)
{
	if (tokens->type != WORD && tokens->type != REDIRECT && tokens->type != HEREDOC)
	{
		printf("minishell: parse error near `%s`\n", tokens->value);
		return (-1);
	}
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			//code
		}
		else if (tokens->type == REDIRECT)
		{
			//code
		}
		else if (tokens->type == HEREDOC)
		{
			//code
		}
		else if (tokens->type == PIPE)
		{
			//code
		}
		else
		{
			printf("minishell: unexpected token near `%s`\n", tokens->value);
			return (-1);
		}
		tokens = tokens->next;
	}
	return (1);
}

t_token	*get_tokens(char *str)
{
	int			i;
	t_token		*head;
	char		*temp;
	int			cursor;

	head = NULL;
	i = -1;
	while (str[++i])
	{
		cursor = -1;
		if (str[i] == WHITE_SPACE)
			continue ;
		else if (str[i] == '|')	
			add_back(&head, new_token(PIPE, ft_strndup(&str[i], 1)));
		else if (str[i] == '<' || str[i] == '>')
		{
			if (!ft_strncmp(&str[i], "<<", 2))
			{
				add_back(&head, new_token(HEREDOC, ft_strndup(&str[i], 2)));
				i++;
				continue ;
			}
			else if (!ft_strncmp(&str[i], ">>", 2))
			{
				add_back(&head, new_token(REDIRECT, ft_strndup(&str[i], 2)));
				i++;
				continue ;
			}
			add_back(&head, new_token(REDIRECT, ft_strndup(&str[i], 1)));
		}
		else if (ft_isalpha(str[i]) || str[i] == '-' || ft_isdigit(str[i]))
		{
			temp = &str[i];
			while (temp[++cursor])
			{
				if (temp[cursor] == ' ' || temp[cursor] == '|' || temp[cursor] == '&' || temp[cursor] == '<' || temp[cursor] == '>')
					break ;
			}
			add_back(&head, new_token(WORD, ft_strndup(temp, cursor)));
			i += cursor - 1;
		}
		else
			add_back(&head, new_token(UNKNOWN, ft_strndup(&str[i], 1)));
	}
	return (head);
}

int main(int argc, char const *argv[])
{
	t_token *tokens;
	t_token	*temp;

	tokens = get_tokens("<< echo 123 | >> -f |grep ;include");
	temp = tokens;
	while (temp)
	{
		printf("%s\n", temp->value);
		temp = temp->next;
	}
	if (parser(tokens) == -1)
		return (1);
	return 0;
}
