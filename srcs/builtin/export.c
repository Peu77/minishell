#include "../../includes/minishell.h"

//todo : probably have to rebuild
int export_command(t_command_test *command)
{
    int i = -1;

    char **arg = ft_split(command->argument, ' ');

    if (!arg || !arg[0])
    {
        while (command->envp[++i])
            printf("%s\n", command->envp[i]);
        return (0);
    }
	if (ft_strnstr(arg[0], "=", ft_strlen(arg[0])))
	{
		char **set_env = ft_split(arg[0], '=');
		if (!set_env || !set_env[0] || !set_env[1])
			return pe("Invalid format. Use key=value.\n");
		if (setenv(set_env[0], set_env[1], 1) != 0)
			return pe("setenv");
		while (command->envp[++i])
			printf("%s\n", command->envp[i]);
		printf("%s=%s\n", set_env[0], set_env[1]);
	}
	else
		printf("Invalid argument. Use key=value to set an environment variable.\n");
	return (0);
}
