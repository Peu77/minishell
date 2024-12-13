#include "../../includes/minishell.h"

static void delete_env_variable(t_env *current, t_env *prev, t_env *env_list)
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
}

int unset_variable(t_env *env, const char *var_name)
{
    t_env *env_list = env;
    t_env *prev = NULL;
    t_env *current = NULL;

    current = env_list;
    while (current)
    {
        if (ft_strncmp(current->variable_name, var_name, ft_strlen(var_name)) == 0 &&
            current->variable_name[ft_strlen(var_name)] == '\0')
        {
            delete_env_variable(current, prev, env_list);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return 1;
}

void print_env_list(t_env *env_list)
{
    t_env *current = env_list;
    while (current != NULL)
    {
        printf("Variable: %s=%s\n", current->variable_name, current->variable_value);
        current = current->next;
    }
}


