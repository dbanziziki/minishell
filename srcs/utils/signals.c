#include "utils.h"

void    action(int signum)
{
    if (signum == SIGQUIT) // "CNTR + \"
    {
		rl_replace_line("", 0);
		rl_redisplay();
        exit (0); /// It should redirect to the main loop and should not display new line.
    }
    else if (signum == SIGINT) // "CNTR + C"
    {
		rl_replace_line("", 0);
		rl_redisplay();/// It should redirect to the main loop and should display new line.
        exit (0);
    }
}

void hook(void)
{
    signal(SIGQUIT, action);
    signal(SIGINT, action);
}
