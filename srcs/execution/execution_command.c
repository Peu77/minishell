#include "../../includes/minishell.h"

static void free_command(char **command)
{
    int i = 0;
    while (command[i])
    {
        free(command[i]);
        i++;
    }
    free(command);
}

void execution_command(t_command *command_list)
{
    char **command = ft_split(command_list->command, ' ');

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        free_command(command);
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
		if (execve(command_list->path, command, NULL) == -1)
        {
            perror("execve failed");
            free_command(command);
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        wait(NULL);
        free_command(command);
    }
}
