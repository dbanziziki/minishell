/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:04:40 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:37:42 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	index;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	index = -1;
	res = (char *)malloc(sizeof(char) * (i + j) + 1);
	if (!res)
		return (NULL);
	while (++index < i)
		res[index] = s1[index];
	index = -1;
	while (++index < j)
		res[index + i] = s2[index];
	res[index + i] = 0;
	return (res);
}
