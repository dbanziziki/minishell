#include "utils.h"

void    action(int signum)
{
    // printf("%10d\n", signum);
    if (signum == SIGQUIT) // "CNTR + \"
        return ;
    else if (signum == SIGINT) // "CNTR + C"
    {
        printf("Here gonna be a new line call.\n");
        exit(0) ;
    }
    // else if (signum == SIGUSR1) // "CNTR + D"
    // {
    //     printf("exit\n");
    //     exit(0);
    // }
}

void hook(void)
{
    signal(SIGQUIT, action);
    signal(SIGINT, action);
    signal(SIGUSR1, action);
}
