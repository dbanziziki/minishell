/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 10:51:41 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:42:30 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s, n);
	res[n] = '\0';
	return (res);
}
