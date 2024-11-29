#include "../../includes/minishell.h"

static void free_command(char **command)
{
    int i = 0;
    // Free each string in the command array
    while (command[i])
    {
        free(command[i]);
        i++;
    }
    // Free the command array itself
    free(command);
}

void execution_command(char *user_prompt)
{
    char **command = ft_split(user_prompt, ' ');

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork failed");
        free_command(command); // Free memory in case of fork failure
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // In child process: execute the command
        if (execve("/bin/ls", command, NULL) == -1)
        {
            perror("execve failed");
            free_command(command); // Free memory if execve fails
            exit(EXIT_FAILURE); // Exit child process on failure
        }
    } 
    else 
    {
        // Parent process: wait for the child to finish
        wait(NULL);
        free_command(command); // Free memory after the child process finishes
    }
}
