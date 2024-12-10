#include "../../includes/minishell.h"




int execution_command(char **arguments, char *path)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        pev("Fork failed");
        return 1;
    }
    if (pid == 0)
    {
		if(!path)
		return (pec(ERROR_PATH));
        if (execve(path, arguments, NULL) == -1)
			return pec(ERROR_EXECVE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            int exit_status = WEXITSTATUS(status);
            return exit_status; 
        }
        return 1;
    }
    return 1;
}

int prepare_execution_command(t_command_test *command)
{
    char *str;
    char **arguments;
	char *temp;
	int result;

		str = ft_strdup(command->command_name);
	
    if (command->argument != NULL)
    {
        temp = ft_strjoin(str, " ");
        free(str);
        str = ft_strjoin(temp, command->argument);
        free(temp);
    }
    arguments = ft_split(str, ' ');
    if (command->path == NULL)
    {
        printf("Command %s not found\n", command->command_name);
        free(str);
    }
    result = execution_command(arguments, command->path);
	free_command_split(arguments);
    return (result);
}
