#include "minishell.h"

void	print_error(char *str, char *arg)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
