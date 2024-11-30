#include "../../includes/minishell.h"

void execution_monitor(t_command *command)
{
    char *list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    int i = 0;

	while (i < NUM_BUILTINS)
	{
		if (ft_strnstr(command->command, list_builtin[i], ft_strlen(command->command)))
		{
			if (i == 5)
				printf("%s \n", pwd());
			return ;
		}
		i++;
	}
	printf("No built-in command found.\n So we will use execve command \n");
	execution_command(command);
}
