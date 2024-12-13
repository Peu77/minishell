#include "../../includes/minishell.h"

int unset(t_command_test *command, t_env *env)
{
    char **arg = ft_split(command->argument, ' ');
    int result = 0;
	int unset_result;

    while (*arg)
    {
        unset_result = unset_variable(env, *arg);
        if (unset_result != 0)
            result = 1;
        arg++;
    }
    return result;
}


