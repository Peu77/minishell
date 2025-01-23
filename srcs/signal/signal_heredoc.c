#include "../../includes/minishell.h"
#include <sys/signal.h>

void	heredoc_sighandler(int sig)
{
	(void)sig;
	unlink("heredoc_temp.txt");
	destroy_minishell(130);
}

void signal_heredoc(void)
{
	signal(SIGINT, heredoc_sighandler);
	signal(SIGTSTP, SIG_IGN);
}
