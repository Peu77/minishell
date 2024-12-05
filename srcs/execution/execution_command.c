#include "../../includes/minishell.h"


void execution_command(t_command *command)
{
	char **arguments = ft_split(command->argument, ' ');

	if (command->path == NULL)
	{
		printf("Command %s not found\n", command->command_name);
		exit(EXIT_FAILURE);
	}
	else if (execve(command->path, arguments, NULL) == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	free_command(&command);
}

