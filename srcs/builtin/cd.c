#include "../../includes/minishell.h"

int cd(t_command *command)
{
    char **path = ft_split(command->argument, ' ');
    char buffer[MAX_PATH];

    printf("Old repository: %s\n", getcwd(buffer, MAX_PATH));
    if (!path[1])
    {
        if (chdir("/") != 0) 
            pe("Problem with the path");
    }
    else 
    {
        if (chdir(path[1]) != 0) 
            pe("Problem with the path");
    }
    printf("New repository: %s\n", getcwd(buffer, MAX_PATH));
	free_command_split(path);
    return (1);
}
