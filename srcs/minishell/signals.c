#include "utils.h"

void    action(int signum)
{
    if (signum == SIGQUIT) // "CNTR + \"
    {
        rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
    else if (signum == SIGINT) // "CNTR + C"
    {
		printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
		// rl_replace_line("\n", 1);
		// rl_on_new_line();
		// rl_redisplay();/// It should redirect to the main loop and should display new line.
        // return ;
		// exit (0);
    }
}

void hook(void)
{
	signal(SIGQUIT, &action);
	signal(SIGINT, &action);
}
