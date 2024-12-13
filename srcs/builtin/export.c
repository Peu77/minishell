#include "../../includes/minishell.h"

int add_env_to_end(t_env *env, char *variable_name, char *variable_value)
{
    t_env *current = env;
    t_env *new_node;

    while (current->next)
        current = current->next;
    new_node = malloc(sizeof(t_env));
    if (!new_node)
    {
        perror("malloc");
        return 1;
    }
    new_node->variable_name = variable_name;
    new_node->variable_value = variable_value;
    new_node->next = NULL;
    new_node->previous = current;
    current->next = new_node;
    return 0;
}

int update_or_add_env_variable(t_env *env, char *variable_name, char *variable_value)
{
    t_env *current = env;
    int found = 0;

    while (current)
    {
        if (ft_strncmp(current->variable_name, variable_name, ft_strlen(variable_name)) == 0)
        {
            free(current->variable_value);
            current->variable_value = variable_value;
            free(variable_name);
            found = 1;
            break;
        }
        current = current->next;
    }
    if (!found)
    {
        if (add_env_to_end(env, variable_name, variable_value) != 0)
        {
            free(variable_name);
            free(variable_value);
            return 1;
        }
    }
    return 0;
}

int extract_variable_name_and_value(char *argument, char **variable_name, char **variable_value)
{
    char *equal_sign = ft_strchr(argument, '=');

    if (!equal_sign || equal_sign == argument || *(equal_sign + 1) == '\0')
        return (1);
    size_t name_len = equal_sign - argument;
    *variable_name = malloc(name_len + 1);
    if (!(*variable_name))
        return pec(ERROR_MALLOC);
    ft_memcpy(*variable_name, argument, name_len);
    (*variable_name)[name_len] = '\0';

    *variable_value = ft_strdup(equal_sign + 1);
    if (!(*variable_value))
    {
        free(*variable_name);
        return pec(ERROR_MALLOC);
    }
    return (0);
}

int free_export_command(t_export *export)
{
    if (export->args)
    {
        free_command_split(export->args); 
        export->args = NULL;
    }
    if (export->variable_name)
    {
        free(export->variable_name);
        export->variable_name = NULL;
    }
    if (export->variable_value)
    {
        free(export->variable_value);
        export->variable_value = NULL;
    }
    return 1;
}

int export_command(t_command_test *command, t_env *env)
{
    t_export export = {0};

    export.args = ft_split(command->argument, ' ');
    if (!export.args)
        return 1;
    while (export.args[export.i] != NULL)
    {
        char *argument = export.args[export.i];
        export.equal_sign = ft_strchr(argument, '=');
        if (!export.equal_sign || export.equal_sign == argument || *(export.equal_sign + 1) == '\0')
        {
            export.result = 1;
            export.i++;
            continue;
        }
        if (extract_variable_name_and_value(argument, &export.variable_name, &export.variable_value) != 0)
            return free_export_command(&export);
        if (update_or_add_env_variable(env, export.variable_name, export.variable_value) != 0)
            return free_export_command(&export);
        export.i++;
    }
    free_command_split(export.args);
    return 0;
}
