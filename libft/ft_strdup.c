/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:03:49 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:37:05 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	i = -1;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (++i < len)
		res[i] = ((char *)s)[i];
	res[i] = '\0';
	return (res);
}
