#include "utils.h"

void	action(int signum)
{
	if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 1);
		rl_redisplay();
		rl_replace_line("", 0);
	}
	else if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 1);
		rl_redisplay();
		rl_replace_line("", 1);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	hook(void)
{
	signal(SIGQUIT, &action);
	signal(SIGINT, &action);
}
