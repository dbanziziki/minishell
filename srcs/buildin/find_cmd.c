#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	find_cmd(t_array cmd, t_array flags)
{
	printf("--%s--\n", (char *)cmd.items[1]);
	printf("--%s--\n", (char *)cmd.items[2]);
	echo((char *)cmd.items[2], (char *)cmd.items[1]);
	return (1);
}
