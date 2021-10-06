/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:24:57 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/10/06 15:24:58 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*skip_whitespace(char *str, t_tokenizer *t)
{
	if (!str)
		return (str);
	while (t->str[t->cursor] && ft_isspace(t->str[t->cursor]))
		t->cursor++;
	str = &(t->str[t->cursor]);
	return (str);
}

t_token	*dollarsign_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	size_t	i;

	i = t->cursor;
	if (!temp[1] || ft_isspace(temp[1]))
	{
		t->cursor++;
		return (new_token(WORD_TOKEN, ft_strndup(temp, 1)));
	}
	while (t->str[t->cursor] && t->str[t->cursor] != ' ')
		t->cursor++;
	token = new_token(DOLLARSIGN_TOKEN, ft_strndup(temp, t->cursor - i));
	if (!token)
		return (NULL);
	return (token);
}

t_token	*simple_token(t_tokenizer *t, char *temp)
{
	t_token	*token;
	int		type;

	if (temp[0] == LEFT_REDIRECT)
		type = LESS_THAN_TOKEN;
	else if (temp[0] == RIGHT_REDIRECT)
		type = GREATER_THAN_TOKEN;
	else
		type = PIPE_TOKEN;
	token = new_token(type, ft_strndup(temp, 1));
	if (!token)
		return (NULL);
	t->cursor++;
	return (token);
}
