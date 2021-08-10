/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:59:20 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:40:41 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*res;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	while (++i < (unsigned int)len)
		res[i] = f(i, s[i]);
	res[i] = '\0';
	return (res);
}
