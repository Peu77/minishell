#include "../../includes/minishell.h"

int execution_command(char **arguments, char *path)
{
    pid_t pid = fork();

    if (pid == -1)
        return pe("Fork failed");
    if (pid == 0)
    {
        if (execve(path, arguments, NULL) == -1)
            return pe("execve failed");
    }
    else
        waitpid(pid, NULL, 0);

    return (1);
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
    free(str);
    free_command(&command);
    return (result);
}
