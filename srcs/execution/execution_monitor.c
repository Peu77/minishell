#include "../../includes/minishell.h"

void execution_monitor(t_command *command, t_pipe *pipe)
{
    char *list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    int i = 0;

	while (i < NUM_BUILTINS)
	{
		if (ft_strnstr(command->argument, list_builtin[i], ft_strlen(command->argument)))
		{
			if (i == 0)
				cd(command);
			else if (i == 1)
				echo(command, 0);
			else if (i == 2)
				env(command);
			else if (i == 3)
				exit_command(pipe, command);
			else if (i == 4)
				export_command(command);
			else if (i == 5)
				printf("%s\n", pwd());
			else if (i == 6)
				unset(command);
			return ;
		}
		i++;
	}
	execution_command(command);
}
