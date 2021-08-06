#include "utils.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	unsigned char *ptr_dest;
	unsigned char *ptr_src;

	ptr_dest = dest;
	ptr_src = (unsigned char *)src;
	i = -1;
	if (!dest && !src)
		return (NULL);
	while (++i < n)
		*(ptr_dest + i) = *(ptr_src + i);
	return (dest);
}

char *ft_strndup(const char *s, size_t n)
{
	char *res;

	if (!s)
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ft_memcpy(res, s, n);
	res[n] = '\0';
	return (res);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (*((char *)s1 + i) && *((char *)s1 + i) == *((char *)s2 + i) && i < n - 1)
		i++;
	if (n)
		return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
	return (0);
}

int ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t ft_strlen(char *str)
{
	size_t len;

	len = -1;
	while (str[++len])
		;
	return (len);
}