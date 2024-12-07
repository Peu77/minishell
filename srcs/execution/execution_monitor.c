#include "../../includes/minishell.h"

int execution_monitor(t_command_test *command)
{
    char *list_builtin[NUM_BUILTINS] = {"cd", "echo", "env", "exit", "export", "pwd", "unset"};
    int i = -1;

	while (++i < NUM_BUILTINS)
	{
		if (ft_strncmp(command->command_name, list_builtin[i], ft_strlen(list_builtin[i]) + 1) == 0)
		{
			if (i == 0)
				return cd(command);
			else if (i == 1)
				return echo(command, 0);
			else if (i == 2)
				return env(command);
			else if (i == 3)
				return exit_command(command);
			else if (i == 4)
				return export_command(command);
			else if (i == 5)
				return pwd();
			else if (i == 6)
				return unset(command);
		}
	}
	return prepare_execution_command(command);
}
