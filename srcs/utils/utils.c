#include "utils.h"

char	*ft_strjoin_sep(char const *s1, char const *s2, int c)
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
	res = (char *)malloc(sizeof(char) * (i + j) + 2);
	if (!res)
		return (NULL);
	while (++index < i)
		res[index] = s1[index];
	res[i++] = c;
	index = -1;
	while (++index < j)
		res[index + i] = s2[index];
	res[index + i] = 0;
	return (res);
}

void	free_tab(char **tab)
{
	int	len;

	len = -1;
	while (tab[++len])
		free(tab[len]);
	free(tab);
}
