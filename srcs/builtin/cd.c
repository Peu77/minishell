#include "../../includes/minishell.h"

int cd(t_command_test *command)
{
    char **path;
	
	path = ft_split(command->argument, ' ');
	if(!path)
		pec(ERROR_SPLIT);
    if (!path[0])
    {
        if (chdir("/") != 0) 
		{
			free_command_split(path);
			return pec(ERROR_PATH);
		}
    }
    else 
    {
        if (chdir(path[0]) != 0) 
		{
			free_command_split(path);
			return pec(ERROR_PATH);
		}
    }
	free_command_split(path);
    return (0);
}
