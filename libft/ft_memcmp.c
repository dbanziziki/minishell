/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:46:01 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:34:52 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = -1;
	while (++i < n && *(s1_ptr + i) == *(s2_ptr + i))
		;
	if (i == n)
		return (0);
	return (*(s1_ptr + i) - *(s2_ptr + i));
}
