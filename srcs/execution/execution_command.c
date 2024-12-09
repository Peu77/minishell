#include "../../includes/minishell.h"



int execution_command(char **arguments, char *path)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        pe("Fork failed");
        return 0;
    }
    if (pid == 0)
    {
        if (execve(path, arguments, NULL) == -1)
        {
            pe("execve failed");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0)
                return 1;
            else
                return 0;
        }
        else
        {
            return 0;
        }
    }
    return 1;
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
    return (result);
}
