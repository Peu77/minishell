#include "../../includes/minishell.h"


int exit_command(t_command_test *command)
{
	char **cmd; 

	if(command->argument == NULL)
		exit(EXIT_SUCCESS);
	cmd = ft_split(command->argument, ' ');
	if(!cmd)
		return pec(ERROR_SPLIT);	
	if (cmd[1]) 
	{
		pev("Error, too many arguments for exit command");
		free_command_split(cmd);
		return 1;
	}
	else
	{
		free_command_split(cmd);
		exit(EXIT_SUCCESS);
	}
}
