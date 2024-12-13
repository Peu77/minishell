#include "../../includes/minishell.h"

void print_env_list(t_env *env_list)
{
    t_env *current = env_list;
    while (current != NULL)
    {
        printf("Variable: %s=%s\n", current->variable_name, current->variable_value);
        current = current->next;
    }
}


int env(t_command_test *command, t_env *env)
{
    if (command->argument)
       return pec("env: too many arguments\n");
	print_env_list(env);
    return 0;
}
