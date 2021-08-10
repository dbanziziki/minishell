/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:37:47 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:24:30 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_nb_len(int n)
{
	size_t	count;

	count = 1;
	n /= 10;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int				size;
	char			*res;
	unsigned int	j;

	size = get_nb_len(n);
	j = n;
	if (n < 0)
	{
		j = -n;
		size++;
	}
	res = ft_strnew(size);
	if (!res)
		return (NULL);
	res[--size] = j % 10 + '0';
	j /= 10;
	while (j)
	{
		res[--size] = j % 10 + '0';
		j /= 10;
	}
	if (n < 0)
		*res = '-';
	return (res);
}
