#include "../../includes/minishell.h"

int unset(t_command_test *command, t_env *env)
{
    char **arg = ft_split(command->argument, ' ');
    t_env *env_list = env;
    t_env *prev = NULL;
    t_env *current = NULL;
    int result = 0;

    while (*arg)
	{
        current = env_list;
        prev = NULL;
		while (current)
		{
			if (ft_strncmp(current->variable_name, *arg, ft_strlen(*arg)) == 0 &&
				current->variable_name[ft_strlen(*arg)] == '\0') 
			{
				if (prev)
					prev->next = current->next;
				else 
					env_list = current->next;
				if (current->next) 
					current->next->previous = prev;
				free(current->variable_name);
				free(current->variable_value);
				free(current);
				break;
			}
			prev = current;
			current = current->next;
		}
		arg++;
	}
	env = env_list;
	return result;
}
