#include "../../includes/minishell.h"

int exit_command(t_pipe *pipe, t_command *command)
{
	char **cmd = ft_split(command->argument, ' ');
	if(cmd[1] && cmd[2])
		pe("Error, too many arguments");
	exit_shell(pipe, EXIT_SUCCESS);
	return (1);
}
