#include "../../includes/minishell.h"

static void	sigint_command(int sig)
{
	(void)sig;
	destroy_minishell(130);
}

static void sigquit_command(int sig)
{
	(void)sig;
	destroy_minishell(131);
}

/*
static void sigtstp_command(int sig)
{
	(void)sig;
	destroy_minishell(131);
}
*/

void	command_signals(void)
{
	signal(SIGINT, sigint_command);
	signal(SIGQUIT, sigquit_command);
//signal(SIGTSTP, sigtstp_command);
}

