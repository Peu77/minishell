#include "../../includes/minishell.h"

int cd(t_command_test *command)
{
    char **path = ft_split(command->argument, ' ');
    char buffer[MAX_PATH];

    printf("Old repository: %s\n", getcwd(buffer, MAX_PATH));
    if (!path[0])
    {
        if (chdir("/") != 0) 
		{
            pev("Problem with the path");
			return (1);
		}
    }
    else 
    {
        if (chdir(path[0]) != 0) 
		{
            pev("Problem with the path");
			return (1);
		}
    }
    printf("New repository: %s\n", getcwd(buffer, MAX_PATH));
	free_command_split(path);
    return (0);
}
