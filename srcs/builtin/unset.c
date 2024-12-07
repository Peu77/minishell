#include "../../includes/minishell.h"

int unset(t_command_test *command)
{
	char **arg = ft_split(command->argument, ' ');
	int i = 0;
	if(!arg[1])
	{
		printf("no argument \n");
		return (0);
	}
	while (arg[++i])
	{
		if (unsetenv(arg[i]) != 0)
			return pe("unsetenv");
	}
	return (1);
}
