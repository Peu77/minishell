#include "../../includes/minishell.h"

void unset(t_command *command)
{
	char **arg = ft_split(command->argument, ' ');
	int i = 1;
	if(!arg[1])
	{
		printf("no argument \n");
		return ;
	}
	while (arg[i])
	{
		if (unsetenv(arg[i]) != 0)
			perror("unsetenv");
		i++;
	}
}
