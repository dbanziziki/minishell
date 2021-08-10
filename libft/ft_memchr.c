/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:45:40 by dbanzizi          #+#    #+#             */
/*   Updated: 2020/11/18 13:45:42 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((unsigned char *)s + i);
	}
	return (NULL);
}
