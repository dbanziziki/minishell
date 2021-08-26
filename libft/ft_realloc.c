#include "libft.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*res;

	res = malloc(size);
	if (!res)
		return (NULL);
	ft_memmove(res, ptr, old_size);
	free(ptr);
	return (res);
}