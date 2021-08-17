#include "utils.h"

void    action(int signum)
{
    if (signum == SIGQUIT) // "CNTR + \"
    {
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
    }
    else if (signum == SIGINT) // "CNTR + C"
    {
		rl_replace_line("\n", 0);
		rl_on_new_line();
		rl_redisplay();/// It should redirect to the main loop and should display new line.
        // exit (0);
    }
}

void hook(void)
{
	signal(SIGQUIT, &action);
	signal(SIGINT, &action);
}
