#include "minishell.h"

t_sig	g_sig;

void	action(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_sig.id != 0)
		{
			ft_putstr_fd("Quit: ", STDERR_FILENO);
			ft_putnbr_fd(SIGQUIT, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("  ", 0);
			rl_redisplay();
			rl_replace_line("", 1);
		}
		g_sig.exit_status = SIGQUIT;
	}
	else if (signum == SIGINT)
	{
		if (g_sig.id == 0)
		{
			g_sig.exit_status = 1;
			rl_on_new_line();
			rl_replace_line("  ", 1);
			rl_redisplay();
			rl_replace_line("", 1);
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			g_sig.exit_status = SIGINT;
			rl_on_new_line();
			rl_replace_line("  ", 1);
			rl_replace_line("", 1);
			printf("\n");
			rl_on_new_line();
		}
	}
}

void	hook(void)
{
	signal(SIGQUIT, &action);
	signal(SIGINT, &action);
}
