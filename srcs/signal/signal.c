#include "../../includes/minishell.h"

static void exit_signal(int signal)
{
    if (signal == SIGUSR1)
	{
        printf("Signal received, exiting signal.\n");
        exit(EXIT_SUCCESS);
    }
}

void signal_waiting()
{
	if (signal(SIGUSR1, exit_signal) == SIG_ERR) 
	{
        perror("Error signal");
        return ;
    }
    while (1)
	{
        pause();
    }
}
