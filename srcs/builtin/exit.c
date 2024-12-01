#include "../../includes/minishell.h"

void exit_command(t_pipe *pipe)
{
    if (pipe->pid_signal > 0)
        kill(pipe->pid_signal, SIGTERM);
    exit(EXIT_SUCCESS);
}
