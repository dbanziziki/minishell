/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:33:22 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:14:03 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;

	res = (unsigned char *)malloc(size * nmemb);
	if (!res)
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}
