/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 12:58:26 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:38:11 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	index;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (destsize == 0)
		return (src_len);
	while (dest[i] && i < destsize)
		i++;
	index = -1;
	while (src[++index] && i < destsize - 1)
		dest[i++] = src[index];
	if (destsize != 0 && destsize >= dest_len)
		dest[i] = '\0';
	if (destsize < dest_len)
		return (destsize + src_len);
	return (dest_len + src_len);
}
