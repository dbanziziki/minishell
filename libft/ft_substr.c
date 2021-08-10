/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:05:54 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:51:20 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	if ((start + len) >= ft_strlen(s))
		j = ft_strlen(s);
	else
		j = len;
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	ret = (char *)malloc(sizeof(char) * j + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (j-- && s[start])
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
