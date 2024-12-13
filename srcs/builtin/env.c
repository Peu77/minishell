#include "../../includes/minishell.h"

int env(t_command_test *command, t_env *env)
{
    if (command->argument)
       return pec("env: too many arguments\n");
	print_env_list(env);
    return 0;
}
