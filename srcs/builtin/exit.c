#include "../../includes/minishell.h"

void exit_command(t_pipe *pipe, t_command *command)
{
	char **cmd = ft_split(command->argument, ' ');
	if(cmd[1] && cmd[2])
	{
		pe("Error, too many arguments");
	}
	else if (pipe->pid_signal > 0)
        kill(pipe->pid_signal, SIGTERM);
    return exit(EXIT_SUCCESS);
}
