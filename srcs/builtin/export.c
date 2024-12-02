#include "../../includes/minishell.h"


void export_command(t_command *command)
{
    int i = 0;

    char **arg = ft_split(command->argument, ' ');

    if (!arg || !arg[1])
    {
        while (command->envp[i])
        {
            printf("%s\n", command->envp[i]);
            i++;
        }
        return;
    }
	if (ft_strnstr(arg[1], "=", ft_strlen(arg[1])))
	{
		char **set_env = ft_split(arg[1], '=');
		if (!set_env || !set_env[0] || !set_env[1])
		{
			printf("Invalid format. Use key=value.\n");
			return;
		}
		if (setenv(set_env[0], set_env[1], 1) != 0)
		{
			perror("setenv");
			return;
		}
		while (command->envp[i])
		{
			printf("%s\n", command->envp[i]);
			i++;
		}
		printf("%s=%s\n", set_env[0], set_env[1]);
	}
	else
	printf("Invalid argument. Use key=value to set an environment variable.\n");
}
