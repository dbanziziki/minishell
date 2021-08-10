/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:51:13 by dbanzizi          #+#    #+#             */
/*   Updated: 2020/11/23 11:51:15 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	dest_ptr = dest;
	src_ptr = (unsigned char *)src;
	i = -1;
	while (++i < n)
	{
		dest_ptr[i] = src_ptr[i];
		if (src_ptr[i] == (unsigned char)c)
			return (dest_ptr + i + 1);
	}
	return (NULL);
}
