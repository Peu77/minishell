#include "../../includes/minishell.h"


int execution_command(char **arguments, char *path)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        pe("Fork failed");
        return 0;  // Return failure if fork fails
    }
    if (pid == 0)  // Child process
    {
        if (execve(path, arguments, NULL) == -1)
        {
            pe("execve failed");
            exit(EXIT_FAILURE);  // Exit child process if execve fails
        }
    }
    else  // Parent process
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
            return WEXITSTATUS(status);  // Return the exit status of the child
        else
            return 0;  // Return failure if the child process didn't exit normally
    }
    return 1;  // Default success return
}


int prepare_execution_command(t_command_test *command)
{
    char *str;
    char **arguments;
	int result;

		str = ft_strdup(command->command_name);
    if (command->argument != NULL)
    {
        char *temp = ft_strjoin(str, " ");
        free(str);
        str = ft_strjoin(temp, command->argument);
        free(temp);
    }
    arguments = ft_split(str, ' ');
    if (command->path == NULL)
    {
        printf("Command %s not found\n", command->command_name);
        free(str);
        return (0);
    }
    result = execution_command(arguments, command->path);
	if (command->saved_stdout)    free(str);
    free_command(&command);
    return (result);
}
