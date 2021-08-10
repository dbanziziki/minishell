/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:46:31 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:39:34 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = ft_strlen(src);
	if (i + 1 < size)
		ft_memcpy(dest, src, i + 1);
	else if (size)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (i);
}
