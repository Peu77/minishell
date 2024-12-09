#include "../../includes/minishell.h"

int exit_command(t_command_test *command)
{
	char **cmd = ft_split(command->argument, ' ');
	if(cmd[0] && cmd[1])
	{
		pev("Error, too many arguments");
		return (1);
	}
	exit(EXIT_SUCCESS);
	return (0);
}
