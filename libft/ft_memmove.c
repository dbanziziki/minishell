/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:46:16 by dbanzizi          #+#    #+#             */
/*   Updated: 2020/11/18 13:46:17 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src_ptr;
	unsigned char	*dest_ptr;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	src_ptr = (unsigned char *)src;
	dest_ptr = (unsigned char *)dest;
	i = -1;
	if (src_ptr > dest_ptr)
	{
		while (++i < n)
			dest_ptr[i] = src_ptr[i];
	}
	else
	{
		while ((int)(--n) >= 0)
			dest_ptr[n] = src_ptr[n];
	}
	return (dest);
}
