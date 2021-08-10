/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbanzizi <dbanzizi@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:01:04 by dbanzizi          #+#    #+#             */
/*   Updated: 2021/05/29 14:45:09 by dbanzizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		found;

	i = -1;
	found = 1;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[++i] && i < len)
	{
		j = 0;
		if (haystack[i] == *needle)
		{
			k = i;
			found = 1;
			while (haystack[k]
				&& needle[j] && haystack[k] == needle[j] && j < len && k < len)
				if (haystack[k++] != needle[j++])
					found = 0;
		}
		if (found && !needle[j])
			return ((char *)haystack + i);
	}
	return (NULL);
}
