#include "minishell.h"
#include "libft.h"
#include <stdio.h>

int	find_cmd(t_array cmd, t_array flags)
{
	// printf("--%s--\n", (char *)cmd.items[1]);
	// printf("--%s--\n", (char *)cmd.items[2]);
	if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "echo"))
		echo((char *)cmd.items[1], (char *)cmd.items[2]);
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "pwd"))
		pwd();
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "cd"))
		change_dir((char *)cmd.items[1]);
	else if ((char *)cmd.items[0] && !ft_strcmp((char *)cmd.items[0], "exit"))
		time_to_exit();
	return (1);
}
