#include "../../includes/minishell.h"

int env(t_command *command)
{
    int i = -1;
    char **arg = ft_split(command->argument, ' ');

	//case env
    if (!arg || !arg[1])
    {
        while (command->envp[++i])
            printf("%s\n", command->envp[i]);
        return (1);
    }
	if (ft_strnstr(arg[1], "=", ft_strlen(arg[1])))
	{
		char **set_env = ft_split(arg[1], '=');
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
	return (1);
}
