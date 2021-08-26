#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
#include <stdio.h>
#include "libft.h"
#include <readline/readline.h>
#include "list.h"

char	*ft_strjoin_sep(char const *s1, char const *s2, int c);
char	*get_env_v(char *key, t_array *var);
#endif
