#include "../../includes/minishell.h"
#include <unistd.h>


void cd(t_command *command)
{
    char **path = ft_split(command->argument, ' ');
    char buffer[MAX_PATH];

    printf("Old repository: %s\n", getcwd(buffer, MAX_PATH));
    if (!path[1])
    {
        if (chdir("/") != 0) 
            perror("Problem with the path");
    }
    else 
    {
        if (chdir(path[1]) != 0) 
        {
            perror("Problem with the path");
        }
    }
    printf("New repository: %s\n", getcwd(buffer, MAX_PATH));

    int i = 0;
    while (path[i]) 
    {
        free(path[i]);
        i++;
    }
    free(path);

    return;
}
