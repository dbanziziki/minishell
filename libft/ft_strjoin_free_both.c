#include "libft.h"

char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	index;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	index = -1;
	res = (char *)malloc(sizeof(char) * (i + j) + 1);
	if (!res)
		return (NULL);
	while (++index < i)
		res[index] = s1[index];
	index = -1;
	while (++index < j)
		res[index + i] = s2[index];
	res[index + i] = 0;
    free(s1);
    free(s2);
	return (res);
}